= 検索を拡張したインテリジェントアプリの開発

ここから本題である、Azure AI Search と GPT-4 omniを使ってプレゼンテーション資料の検索の拡張をしたインテリジェントアプリの開発について、アーキテクチャの解説、実際のアプリの実装手順、今後の展望について説明します。

== アーキテクチャの解説

アプリケーションのアーキテクチャは下図になり、5 つの Azure サービスを利用しています。

//image[architecture][アプリケーションのアーキテクチャ]{
//}

このアーキテクチャにおいて、インデックスを作成するまでの流れは以下になります。

① インデクサー実行：インデクサーを実行し、Blob Storage にアップロードされている画像データに対して組み込みのスキルによる OCR や、カスタムスキルによる画像内の図などのイラストの特徴付けや分類を行う。

② カスタムスキル実行：AI Search のカスタムスキルにより、Azure OpenAI Service にリクエストを投げるための Azure Functions が起動する。

③ カスタムスキル実行：Azure Functions からのリクエストにより、与えられたプロンプトと画像情報を元に、画像内の図などのイラストに対する分析を行う。

さらに、ユーザーがアプリに対して検索をかけて、検索結果が返されるまでの流れは以下になります。

① 検索：ローカル PC に保存されている HTML と JavaScript で書かれたデモアプリに対して、ユーザーがプレゼンテーション資料を行うための検索クエリを入力する。

② デザイン検索：デモアプリはユーザーに代わって、Azure AI Search に対してデザインの検索を行い、検索結果を受け取る。

③ ファイル取得：検索結果のmetadata_storage_pathから Blob Storage に保存されている画像を取得する。

④ 検索結果：AI Search から受け取った検索結果と、Blob Storage から取得した画像データを元に、ユーザーに対して検索結果を表示する。

== 実装手順

これらのアプリケーションは Azure ポータルで操作して構築することも可能ですが、本書では Bicep を使って構築することにします。なぜなら、Azure ポータルはUI が定期的に変化し、執筆時点での操作画面と読者の方々の時の操作画面が異なる可能性を懸念したためです。これから、Bicep を使ってアプリケーションをデプロイするための手順について説明します。ただし、注意点として以下からはAzure OpenAI Serviceが利用できる前提で話を進めるため、サブスクリプションに対する申請ができていない場合は申請フォーム@<fn>{sinsei}から申請してください。

//footnote[sinsei][申請フォーム, https://customervoice.microsoft.com/Pages/ResponsePage.aspx?id=v4j5cvGGr0GRqy180BHbR7en2Ais5pxKtso_Pz4b1_xUNTZBNzRKNlVQSFhZMU9aV09EVzYxWFdORCQlQCN0PWcu]


=== Bicep とは (コラム)

Bicepとは、Azureリソースを管理やデプロイするための言語です@<fn>{bicep}。Bicep は Azureのインフラストラクチャをコードで表現する、所謂 IaC (Infrastructure as a Code) です。また、Bicep は全ての Azure リソース と API のバージョンをサポートしている上、JSONベースのARMテンプレートよりも読みやすい特徴があります。このような特徴から、Bicepは Azureリソースのデプロイを行うための強力なツールとして、Azure のクラウドエンジニアに広く受け入れられています。@<br>{}

//footnote[bicep][Bicep とは, https://learn.microsoft.com/ja-jp/azure/azure-resource-manager/bicep/overview?tabs=bicep]

本書で扱うサンプルアプリケーションのソースコードが保存されているリポジトリはこちらになります。

https://github.com/yus04/slide-search-app

こちらのリポジトリのコードを使って、サンプルアプリケーションをデプロイする手順については以下の流れになります。

① 環境構築

② ソースコードのクローン

③ Azure リソースとアプリケーションのデプロイ

それでは、それぞれのステップにて詳細の手順を説明します。

① 環境構築本書では環境構築のセットアップの手間を省くために、Azure Cloud Shell という Azure 上で利用可能な Shell を利用します。Azure Cloud Shell ではデフォルトで Azure Developer CLI という、Bicep で記述された Azure リソースをデプロイするためのツールや、git などの本書で扱うツールがデフォルトでインストールがされています。

=== Azure Developer CLI とは (コラム)

Azure Developer CLI とは、アプリケーションをローカル開発環境から Azure に移動させるのを効率的にするツールです@<fn>{azd}。開発者は、アプリの構築、デプロイ、監視、管理などのタスクをAzure Developer CLIを通じて実行できます。Azureのサービスとのやり取りをシンプルにし、自動化やスクリプト化による効率的な作業を可能にします。

//footnote[azd][Azure Developer CLI とは, https://learn.microsoft.com/ja-jp/azure/developer/azure-developer-cli/overview]

Azure Cloud Shell は、ヘッダーにあるターミナルのアイコンを押すことで表示されます(赤枠内のアイコン)。Azure Cloud Shell を使うには Storage Accountが必要なので、作成していない読者の方はこの際に作成をして下さい。

//image[cloudshell][Azure Cloud Shell を起動した様子]{
//}

Azure Cloud Shell が起動したことを確認できれば、開発環境のセットアップは終了です。

② ソースコードのクローン開発環境のセットアップの次は、ソースコードのクローンを行います。クローンするソースコードは永続的なストレージに保存をするために、Azure Cloud Shell 上で clouddrive ディレクトリに移動してからクローンを実行してください。クローン後、ls コマンドを実行することでクローンしたソースコードを含むフォルダ slide-search-app が表示されます。

//emlist{
cd clouddrive
git clone https://github.com/yus04/slide-search-app
ls
//}

//image[cloudshell_after][Azure Cloud Shell で実行した結果]{
//}

./src/setupaisearch.sh は azd up 時に実行されるように azure.yaml で定義されているため、chmod コマンドにより、事前にファイルに実行権限を与えます。

//emlist{
cd slide-search-pp
chmod +x src/setupaisearch.sh
//}

//image[setupaisearch][実行権限の付与]{
//}

補足：setupaisearch.sh への実行権限の付与についてAzure Cloud Shell でソースコードをクローンした状態で ls -lh src/setupaisearch.sh を実行すると確認できますが、今回のケースでは setupaisearch.sh にもともと実行権限が付与されているため、chmod コマンドを実行する必要はありません。

//image[auth_check][実行権限の確認]{
//}

③ Azureリソースとアプリケーションのデプロイazd up でAzure リソースの作成とアプリケーションのデプロイをしていきます。

//emlist{
azd up
//}

まず、「Enter a new environment name」 と言われるので、環境名を入力します。これはリソースグループ名にもなるため、既存のリソースグループ名と重複が無いように決定します。また、「Select an Azure Subscription to use」と言われるので、利用する Azure サブスクリプションを選択したあと、「Select an Azure location to use」と言われるので、Azureリソースを作成するリージョンを決定します。infra/main.bicep を確認すると確認できますが、GPT-4o だけは GA されている eastus で固定にしておりますので、お好きなリージョンを選択ください。特にこだわりが無ければ東日本リージョン (japaneast) にします。すると、以下の画面のようにAzureリソースのプロビジョニングが開始します。

//image[azdup][azd up 後の画面]{
//}

(azd up を実行した後にいくつかの質問事項に回答し、Azureリソースのプロビジョニングが開始している様子)デプロイには10~15 分程度の時間がかりますが、最終的にはデプロイが完了し、以下の画面のような画面が表示されます。

//image[azdprovisioning][azd up 後のプロビジョニングの様子]{
//}

無事、デプロイ完了の画面が表示されたらAzure ポータルを確認して、必要な Azure リソースや AI Search のデータソース、インデックス、スキルセット、インデクサー、が作成されていることを確認します。サンプルアプリのドキュメントは65つあるため、インデックスのドキュメント数が65になっていればデプロイは成功です。

//image[aisearchcreate][必要なリソースの確認]{
//}

//image[aisearchcreate2][必要なリソースの確認]{
//}

//image[aisearchcreate3][必要なリソースの確認]{
//}

== 利用方法

それでは、デプロイしたアプリケーションを利用していきます。最初にAzure ポータルで作成済みのAzure AI Search を選択します。その次に、左側のメニューバーにある「インデックス」を選択し、「slide-search-app-index」を押します。

//image[sousa1][操作 1]{
//}

上のタブに「デモアプリの作成」があるので、選択したあとモーダルで表示される「CORSを有効にして実行する」を押します。

//image[sousa2][操作 2]{
//}

この画面では、個々の結果のカスタマイズをしていきます。縮小版には「metadata_storage_path」を選択し、タイトルには「metadata_storage_name」を選択し、説明には「explaination」を選んだ上で「次へ」を押します。

//image[sousa3][操作 3]{
//}

サイドバーはカスタマイズ不要なのでそのまま「次へ」を押します。

//image[sousa4][操作 4]{
//}

候補のカスタマイズも不要なので、そのまま「デモアプリの作成」を行います。

//image[sousa5][操作 5]{
//}

デモアプリの準備が完了したら、「ダウンロード」を押します。

//image[sousa6][操作 6]{
//}

エクスプローラーのダウンロードを見るとAzSearchというファイルがあるので、選択する。

//image[sousa7][操作 7]{
//}

以下のような画面が表示される。

//image[sousa8][操作 8]{
//}

検索バーの右にある虫眼鏡のアイコンを選択すると、インデックスに登録されているプレゼンテーション資料の一覧が表示されれば、無事デモアプリの作成は成功です。

//image[sousa9][操作 9]{
//}

=== デモアプリを使った検索

//image[human][「人」のイラストが載っている資料の検索]{
//}

//image[flow][「フロー図」で書かれた資料の検索]{
//}

「JISEC」の企業ロゴが載っている資料の検索

//image[logo][「JISEC」の企業ロゴが載っている資料の検索]{
//}

「ビル」の写真を含む資料の検索

//image[building][「ビル」の写真を含む資料の検索]{
//}

=== サンプルアプリの解説

==== プロンプトの解説

サンプルアプリのリポジトリ(https://github.com/yus04/slide-search-app)にあるファイルにも書かれていますが、GPT-4oに渡しているプロンプトは以下のものになります。

//emlist{
あなたはプレゼンテーション資料に含まれるものを様々な項目に対して特定する人です。以下の分析項目について調査し、指定された json 形式で出力してください。資料に含まれるデザインの種類に関しては、デザインの種類の詳細の中から選択してください。ただし、該当しない項目については空文字で回答し、該当する項目が複数ある場合は空白スペース区切りで回答して下さい。

## 分析項目
・資料の説明 (50 文字程度)
・資料に含まれているイラスト
・資料に含まれている写真にある物
・資料に含まれているデザインの種類
・資料に含まれているロゴの企業名

## デザインの種類の詳細
・グラフ (棒、円、折れ線、散布図)
・表
・リスト
・階層図
・概念図
・カレンダー
・ロードマップ
・業務フロー図
・システム図
・ダイアグラム
・プロセスマップ

## 回答 json 形式    {"explanation":"","illustration":"","photo":"","design":"","logo":""}
//}

GPT-4oのモデルは json モードの対象外のため@<fn>{json}、回答はjson形式になるようプロンプトで指示を与えています。

//image[jsonsupport][JSON モードのサポートについて]{
//}

//footnote[json][JSON モードを使用する方法について説明します, https://learn.microsoft.com/ja-jp/azure/ai-services/openai/how-to/json-mode?tabs=python#json-mode-support]

==== インデックスの解説

AI Search のインデックスを検索してみると確認できますが、インデックスのスキーマは以下のものになっています。

//image[indexschema][インデックスのスキーマ]{
//}


textはAI Servicesの組み込みスキルによるものですが、それ以外のフィールドについてはGPT-4oによってエンリッチされた情報になります。