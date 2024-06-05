= Streamlitを用いたフロントエンド開発

== Streamlitとは

Streamlitは、データサイエンティストや機械学習エンジニアが、PythonでインタラクティブなWebアプリケーションを簡単に作成できるオープンソースのフレームワークです。@<fn>{streamlit}Streamlitを使うことで、コーディングの知識が少なくても、データの可視化や分析結果の共有をWeb上で実現できます。

==={1} 主な特徴

 1. @<b>{シンプルな構文}: Streamlitの構文は非常にシンプルで、Pythonの知識があれば簡単に習得できます。複雑なWeb開発の知識は必要ありません。
 2. @<b>{インタラクティブなウィジェット}: スライダー、ボタン、チェックボックスなどのウィジェットを簡単に追加でき、ユーザーが動的にパラメータを変更したり、操作したりできるアプリケーションを作成できます。
 3. @<b>{リアルタイム更新}: コードを変更すると、Webページが自動的に更新されるため、開発効率が向上します。
 4. @<b>{データ可視化}: MatplotlibやPlotlyなどのライブラリと連携し、グラフやチャートを簡単にWebページに埋め込むことができます。
 5. @<b>{キャッシュ機能}: 計算結果をキャッシュすることで、パフォーマンスを向上させることができます。

例えば、以下のようなコードで、タイトルとスライダーを表示するだけの簡単なWebアプリケーションを作成できます。

//emlist[][python]{
import streamlit as st

st.title('Streamlitデモ')
x = st.slider('xの値', 0, 100, 50)
st.write('x:', x)
//}

このコードを実行すると、ブラウザに以下のような画面が表示されます。スライダーを動かすことで、"x:"の値がリアルタイムに変化します。

//image[streamlitdemo][Streamlitデモ画面][scale=1.0]{
//}

Streamlitのギャラリー@<fn>{streamlit_gallery}には、様々なサンプルアプリケーションが公開されており、Streamlitで何ができるのかを具体的にイメージできます。

//footnote[streamlit][Streamlit とは, https://streamlit.io/]
//footnote[streamlit_gallery][Streamlit のギャラリー, https://streamlit.io/gallery]

== Azure App Serviceとは

Azure App Serviceは、Webアプリケーション、REST API、モバイルバックエンドなどをホストするためのMicrosoft Azureのフルマネージドサービスです。開発者はインフラの管理に煩わされることなく、アプリケーションの開発に集中できます。StreamlitなどのPythonフレームワークで開発したWebアプリケーションも簡単にデプロイできます。

==={2} 主な特徴

 1. @<b>{複数の言語とフレームワークに対応}: .NET、.NET Core、Java、Ruby、Node.js、PHP、Python など、様々なプログラミング言語とフレームワークに対応しています。
 2. @<b>{DevOpsの統合}: GitHub、Azure DevOps、Bitbucketなどのソース管理サービスと連携し、継続的なデプロイメントを自動化できます。
 3. @<b>{高可用性とスケーラビリティ}: 複数のインスタンスでアプリケーションを実行し、負荷分散を行うことで、高可用性とスケーラビリティを実現できます。また、トラフィックの変動に応じて自動的にスケールアップ・スケールダウンできるため、常に最適なパフォーマンスを維持できます。
 4. @<b>{セキュリティ}: 組み込みの認証・認可機能やSSLサポートなど、セキュリティ面も充実しています。
 5. @<b>{多様なデプロイ方法}: FTP、Web Deploy、Git、コンテナなど、様々なデプロイ方法に対応しています。
 6. @<b>{監視とログ}: アプリケーションの稼働状況を監視するための機能や、ログを記録するための機能が提供されています。
 7. @<b>{従量課金制}: 利用した分だけ料金が発生する従量課金制なので、コスト効率良くWebアプリケーションを運用できます。

Azure App Serviceは、Webアプリケーションを迅速かつ簡単にデプロイし、運用するための強力なプラットフォームです。開発者はインフラの管理に煩わされることなく、アプリケーションの開発に集中できます。@<b>{今回開発するStreamlitアプリケーションも、Azure App Serviceにデプロイすることで簡単に公開できます。}

== 開発環境の準備

Azure App Service にデプロイする前に、ローカル環境で Streamlit アプリケーションを開発・実行するための準備を行いましょう。

=== 開発環境を整えるための実行手順

==== @<b>{リポジトリのクローン:}

//emlist[][bash]{
git clone https://github.com/Azure-study-project/search_app_front.git
cd search_app_front
//}

上記のコマンドを実行して、サンプルアプリケーションのリポジトリをクローンし、作業ディレクトリに移動します。

==== @<b>{Python 仮想環境の作成:}

//emlist[][bash]{
python -m venv venv
//}

Python の仮想環境を作成します。仮想環境を使うことで、プロジェクトごとに必要なライブラリを独立して管理できます。

==== @<b>{仮想環境のアクティベート:}

//emlist[][bash]{
source venv/bin/activate  # macOS/Linux
venv\Scripts\activate     # Windows
//}

作成した仮想環境をアクティベートします。ターミナルのプロンプトに @<tt>{(venv)} が表示されれば、アクティベート成功です。

==== @<b>{必要なライブラリのインストール:}

//emlist[][bash]{
pip install -r requirements.txt
//}

@<tt>{requirements.txt} に記載されている必要なライブラリをインストールします。

==== @<b>{環境変数の設定}:

//emlist[][bash]{
cp .env.template .env
//}

@<tt>{.env.template} ファイルを @<tt>{.env} ファイルにコピーし、それぞれの値を実際の値に置き換えます。

@<tt>{.env} ファイルは、以下のように編集します。

//emlist{
USE_MOCK=false
AZURE_SEARCH_ENDPOINT=your_search_endpoint
AZURE_SEARCH_API_KEY=your_search_api_key
AZURE_SEARCH_INDEX_NAME=your_index_name
//}

各項目には、Azure ポータルで作成した Azure AI Search の情報を設定します。

 * @<tt>{USE_MOCK}: 3 章までで本番のデータを上手く準備できた場合は @<tt>{false} に設定します。データが準備できていない場合は @<tt>{true} に設定し、モックデータを使用します。
 * @<tt>{AZURE_SEARCH_ENDPOINT}: Azure AI Search のエンドポイント（例: @<tt>{https://[your_search_service_name].search.windows.net}）
 * @<tt>{AZURE_SEARCH_API_KEY}: Azure AI Search の管理 API キー
 * @<tt>{AZURE_SEARCH_INDEX_NAME}: 作成したインデックスの名前

==== @<b>{アプリケーションの起動:}

//emlist[][bash]{
python -m streamlit run Top.py  --server.port 8000 --server.address 0.0.0.0
//}

上記のコマンドを実行すると、Streamlit アプリケーションが起動し、ブラウザで @<tt>{http://localhost:8000} にアクセスすることで、開発中のアプリケーションを確認できます。

//image[searchapptop][トップページ][scale=1.0]{
//}

//image[searchappsearch][検索ページ][scale=1.0]{
//}

うまくアプリケーションが立ち上がっている場合は、上の画像のような画面が表示されます。

== Azure App Serviceへのデプロイ

開発したStreamlitアプリケーションをAzure App Serviceにデプロイする方法を説明します。Azure CLIを用いて、以下の手順でデプロイを行います。

=== Azure CLIでのログイン
Azure CLIを使用してAzureにログインします。

//emlist[][bash]{
az login
//}

ブラウザが開き、Azureアカウントへのログインを求められます。ログインが完了すると、ターミナルにサインイン成功のメッセージが表示されます。

==== リソースグループの作成

Azureにリソースグループを作成します。

//emlist[][bash]{
az group create --name <リソースグループ> --location japaneast
//}

 * リソースグループ: 任意のリソースグループ名。

==== App Serviceプランの作成
次に、App Serviceプランを作成します。

//emlist[][bash]{
az appservice plan create --name <AppServiceプラン> --resource-group <リソースグループ> --sku <SKU> --is-linux
//}

 * AppServiceプラン: 任意のApp Serviceプラン名。
 * リソースグループ: 作成したリソースグループ名。
 * SKU: 使用する価格プラン。

==== Webアプリケーションの作成

Webアプリケーションを作成します。

//emlist[][bash]{
az webapp create --resource-group <リソースグループ> --plan <AppServiceプラン> --name <Webアプリケーション名> --runtime "PYTHON:3.10"
//}

 * リソースグループ: 作成したリソースグループ名。
 * AppServiceプラン: 作成したApp Serviceプラン名。
 * Webアプリケーション名: 任意のWebアプリケーション名。
 * "PYTHON:3.10": Python 3.10 ランタイムを指定。

==== スタートアップコマンドの設定
スタートアップコマンドを設定します。

//emlist[][bash]{
az webapp config set --resource-group <リソースグループ名> --name <Webアプリケーション名> --startup-file "./startup.sh"
//}

 * リソースグループ: 作成したリソースグループ名。
 * Webアプリケーション名: 作成したWebアプリケーション名。

==== アプリケーションの設定
アプリケーションの環境変数の設定を行います。

//emlist[][bash]{
az webapp config appsettings set --resource-group <リソースグループ名> --name <Webアプリケーション名> --settings USE_MOCK=false AZURE_SEARCH_ENDPOINT="<Azure AI Search のエンドポイント>" AZURE_SEARCH_API_KEY="<Azure AI Search の API キー>" AZURE_SEARCH_INDEX_NAME="<Azure AI Search のインデックス名>"
//}

 * リソースグループ: 作成したリソースグループ名。
 * Webアプリケーション名: 作成したWebアプリケーション名。
 * USE_MOCK: モックデータを使用する場合は @<tt>{true}、本番データを使用する場合は @<tt>{false}。
 * AZURE_SEARCH_ENDPOINT: Azure AI Search のエンドポイント（例: https://[your_search_service_name].search.windows.net）。
 * AZURE_SEARCH_API_KEY: Azure AI Search の管理 API キー。
 * AZURE_SEARCH_INDEX_NAME: 作成したインデックスの名前。

==== アプリケーションのデプロイ

デプロイの準備として、クローンしたリポジトリのディレクトリに移動し、以下のコマンドを実行します (このコマンドは、必ずプロジェクトのルートディレクトリから行ってください)。

//emlist[][bash]{
az webapp up --resource-group <リソースグループ> --name <Webアプリケーション名> --sku <SKU> --runtime "PYTHON:3.10"
//}

 * リソースグループ: 作成したリソースグループ名。
 * Webアプリケーション名: 作成したWebアプリケーション名。
 * SKU: 使用する価格プラン。

==== 動作確認
Webブラウザでアプリケーションにアクセスして動作を確認します。
WebアプリケーションのURLにアクセスした際に、ローカルで開発したアプリケーションと同様の画面が表示されれば、デプロイが成功しています。