(Azure AI Search と GPT-4 omniを使ったプレゼンテーション資料の検索の拡張)
Azure AI Search と GPT-4 omni を使ったプレゼンテーション資料の
検索を拡張したインテリジェントアプリの開発

はじめに
この技術書は、2024年5月現在でGPTの最新モデルであるGPT-4 omni (GPT-4o)を使ったユースケースとして、プレゼンテーション資料の拡張の検索を拡張したインテリジェントアプリの開発について述べています。GPT-4oはテキスト、画像、動画、音声を入出力できるマルチモーダルなモデルであり、本技術書の例では、テキストと画像を入力と受け取ることで従来のテキストのみによる資料検索の拡張を図っています。
プレゼンテーション資料の検索を行いたい場合、Microsoftのエコシステムの中に限っても資料を探す方法は多岐にわたります。例えば、Bingでは職場向けの検索ができ、検索に関連するword、PowerPoint、SharePoint等の資料を探しだすことができます。Copilotを利用した社内文書検索では、CopilotやMicrosoft 365 CopilotがMicrosoft Graph APIを介してアクセスできるファイルの中から関連する資料を検索し、ドキュメントを得ることができます。また、SharePointのような社内のポータルサイトやTeamsによるコミュニケーションアプリ、Outlookなどのメールを通じた検索方法も一般的です。しかし、これらの従来の検索方法にはいくつかの制限があります。例えば、テキスト以外の情報を含む資料や、資料に含まれる図や画像に関する情報を利用した検索が困難です。現状では、テキスト情報に依存しており、テキスト以外の情報を持つ資料に対する検索精度や効率性に課題があります。そこで、これらの限界を克服し、プレゼンテーション資料の検索を拡張するためには、新たなアプローチが必要です。まず、GPT-4oの画像認識技術や自然言語処理技術を活用して、資料内の図や画像に対する検索機能を強化することが考えられます。これにより、テキスト以外の情報を含む資料に対する検索の精度と効率性を向上させることができます。さらに、資料のメタデータやタグ付けを活用して、テキスト以外の情報も含めた効果的な検索を実現することが重要です。これにより、資料の属性や特徴に基づいた高度な検索が可能になります。このように、新たな技術とアプローチを活用することで、従来のプレゼンテーション資料の検索方法の限界を克服し、より効率的で精度の高い検索体験を提供することが可能になり、これにより、組織内の知識共有や情報アクセスが向上し、業務効率の向上に貢献します。
本技術書では、上記にある新しいアプローチを提案する内容になっています。また、提案では様々なAzureサービスを利用していますが、それぞれの製品に対する説明をしているため、Azure初学者の方でも理解しやすい内容になっています。この本ではGPT-4oでデプロイしたインテリジェントアプリを手軽に試せるようにテンプレート化しており、実際にご自身の環境で動かすことで簡単にGPT-4oの威力をご体感頂けます。そして、最終的には読者がGPT-4oを活用したインテリジェントアプリの開発に自信を持ち、実際のプロジェクトやビジネスに応用できるようになることをゴールとしています。

 
目次
	Azure 製品紹介
	Azure AI Search
	Azure AI Services
	Azure OpenAI Services
	Azure Functions
	Azure Blob Storage
	検索を拡張したインテリジェントアプリの開発
	アーキテクチャの解説
	実装手順
	利用方法
	今後の展望
	おわりに
 
	Azure 製品紹介
	Azure AI Search
	Azure AI Search とは
Azure AI Search (旧称：Azure Cognitive Search) は、Azure のクラウドプラットフォーム上で提供される、高度な検索ソリューションです(注釈１)。このサービスを利用することで、豊富なデータセットからの効率的な情報検索を実現できます。

![image](https://github.com/yus04/opc-iot-demo/assets/49590084/51842498-f373-43b2-b474-f34291d5611a)
 
(注釈１)

Azure AI Search はセマンティックランク付けによって、テキストベースでのクエリに対して、検索結果の精度やパフォーマンスを向上させます(注釈２)。また、インデクサーによって自動化されたインデックス作成や、組み込みスキルによるインデックス情報のエンリッチ化、カスタムスキルによる高度なスキル構築など、多彩な機能を提供します(注釈３)。そのため Azure AI Search は、電子商取引プラットフォーム、コンテンツ管理システム、カスタマーサポートポータル、教育機関の資料検索システムなど、様々なプラットフォームにて情報検索機能の強化のために活用されています。

(注釈１)
「Azure AI Search とは」
https://learn.microsoft.com/ja-jp/azure/search/search-what-is-azure-search
(注釈2)
「Azure AI Search でのセマンティック ランク付け」
https://learn.microsoft.com/ja-jp/azure/search/semantic-search-overview
(注釈３)
「Azure AI Search の機能」
https://learn.microsoft.com/ja-jp/azure/search/search-features-list

	Azure AI Search の主要機能
ここでは、Azure AI Search を使った検索システムを構築する上で、必ず知っておかないといけない主要機能について簡単に解説します。

	データソース
データソースとは、検索対象となるデータの元となるリソースやデータストアのことを指し、検索エンジンがインデックス化するデータの情報源となるものです。具体的には、Azure SQL Database、Azure Cosmos DB などのデータベースや、Azure Table Storage、Azure Blob Storage といったストレージ、SharePoint やサードパーティーのサービスをデータソースとして利用することができます(注釈１)。

![image](https://github.com/yus04/opc-iot-demo/assets/49590084/719e265e-bb0d-4942-956f-1bd63a2a042f)
 
(注釈１)
Azure AI Search では、これらのデータソースからデータを取得し、利用可能な形式に変換してインデックスに格納することで、ユーザーが高速で効率的な検索を実行できるようになります。

(注釈１)
「データ ソース ギャラリー」
https://learn.microsoft.com/ja-jp/azure/search/search-data-sources-gallery

	インデックス
インデックスとは、検索エンジンがデータを効率的に検索可能な形式で格納するための構造化されたデータの集合を指します(注釈１)。検索対象となるデータソースのデータをコピーして構造化しておくことで、検索クエリの高速な実行や結果の取得を支援します。インデックスには、フィールドと呼ばれる、データの特定の属性やカテゴリを表すフィールドを含んでいます。フィールドの例には、製品名、価格、カテゴリなどがあります。インデックスは、Azure AI Search が提供する検索機能を活用するための中心的なコンポーネントであり、データの高速な検索や検索結果の適切な表示を実現する上で重要な役割を果たします。

(インデックスの例をスクリーンショットして表示、json 形式でも azure ポータル画面でも)

(注釈１)
「Azure AI Search の検索インデックス」
https://learn.microsoft.com/ja-jp/azure/search/search-what-is-an-index

	スキルセット
スキルセットとは、テキストや画像などのコンテンツを解析し、その情報を構造化するための一連の処理ステップのことであり、よりリッチなインデックスを構築するためにドキュメントをエンリッチするために使用されます。
 
![image](https://github.com/yus04/opc-iot-demo/assets/49590084/497cc6db-7ce2-4b0f-a2c3-09a1067efd8f)

(注釈１)
Azure AI Search の組み込みのスキルセットには、テキストデータに対するスキルセットとして、テキスト解析、キーフレーズ抽出、エンティティ抽出、言語検出などの処理を行うスキルや、画像に対するスキルセットとして、オブジェクト検出、顔検出、画像の特徴量抽出などの処理を行うスキルセットがあります(注釈２)。このように、スキルセットは Azure AI Search が効果的にコンテンツを理解して、検索、分析、等の操作を行うための補助を行う機能です。ただし、組み込みのスキルは限られた数のドキュメントしか無料でエンリッチすることができないので、基本的には後述する Azure AI Services のリソースをアタッチする必要があります。

(注釈１)
「Azure AI Searchでのスキルセットの概念」
https://learn.microsoft.com/ja-jp/azure/search/cognitive-search-working-with-skillsets
(注釈２)
「インデックス付け中に追加処理を行うスキル (Azure AI Search)」
https://learn.microsoft.com/ja-jp/azure/search/cognitive-search-predefined-skills
(注釈３)
「Azure AI マルチサービス リソースを Azure AI Search のスキルセットにアタッチする」
https://learn.microsoft.com/ja-jp/azure/search/cognitive-search-attach-cognitive-services?tabs=portal%2Cportal-remove

	カスタムスキル (コラム)
スキルセットに関連して、カスタムスキルという、ユーザーが独自の処理ロジックを組み込んだスキルがあります。通常、Azure AI Search では、テキストや画像などのコンテンツに対する組み込みスキルを提供していますが、特定の要件や高度な要求に対応するためには、これらのスキルだけでは不十分です。そのような場合に使われるのがカスタムスキルであり、スキルの柔軟性や拡張性を高めることができます。カスタムスキルはの一般的なホスティング先としては、Azure Functions やコンテナーになります(注釈１)。

(注釈１)
「Azure AI Search エンリッチメント パイプラインにカスタム スキルを追加する」
https://learn.microsoft.com/ja-jp/azure/search/cognitive-search-custom-skill-interface

を構築し、Azure AI Search のパイプラインに組み込むことで、独自の処理を適用できます。

例えば、テキストデータに対するカスタムスキルを作成することで、特定のテキストパターンの検出、カスタム言語モデルの適用、特定のエンティティの抽出などを行うことができます。また、画像データに対するカスタムスキルを作成することで、特定のオブジェクトの識別、カスタムフィルタリング、画像の特徴量抽出などを行うことができます。

カスタムスキルは、Azure Cognitive Search の柔軟性と拡張性を高め、ユーザーが特定の要件に応じて検索や分析を行う能力を向上させます。

	インデクサー
インデクサーはデータソースからデータを取得し、検索可能な形式に変換して自動的にインデックスに格納する機能を指します。インデクサーは、以下のようなフローでそれぞれのタスクを実行します。

 ![image](https://github.com/yus04/opc-iot-demo/assets/49590084/8ec9be50-e117-4527-b26b-c1d5db418fb9)

(注釈１)

ステージ１ (ドキュメント解析)：インデクサーはまず最初に、データベースや Blob ストレージなどの様々なデータソースに対して、テキストや画像、メタデータなどのデータを取得します。
ステージ２ (フィールドマッピング)：インデクサーは次に、取得したデータを検索エンジンで効率的に検索できる形式に変換するために、データのフィールドのマッピングを実施します。
ステージ3 (スキルセットの実行)：そして、インデクサーはスキルセットが定義されていた場合は、インデックスをエンリッチ化するためにスキルセットを実行します。スキルセットには、OCR や 翻訳、テキスト分割、画像分析などの組み込みのスキルや、カスタムスキルを用いて独自にスキルセットを構築することができます。
ステージ４ (出力フィールドマッピング)：さらに、スキルセットが定義されておりドキュメントのエンリッチ化が行われた場合には、インデクサーはエンリッチされたドキュメントを検索可能な形式に変換するために、データの出力フィールドマッピングを実施します。
ステージ5 (インデックスへの格納)：最後にインデクサーは、マッピングされたデータをインデックスに格納します。

また、インデクサーは上記のステージ１からステージ５を定期的に実行することで、データソースからの新しいデータや変更されたデータからインデックスを更新します。これにより、検索エンジンが最新の情報を提供できるようになります。

(注釈１)
「インデックス作成のステージ」
https://learn.microsoft.com/ja-jp/azure/search/search-indexer-overview#stages-of-indexing

	Azure AI Services
Azure AI Servicesは、クラウドベースのAIサービスのセットです。これらのサービスは、企業や開発者がAI機能をアプリケーションに統合することを容易にするために設計されており、以下のような主要な機能を提供しています。

機能	説明
分析サービス	画像と動画の分析、物体検出、顔認識、文字認識（OCR）等
音声サービス	音声認識、音声合成、音声翻訳、スピーカー認識 等
言語サービス	テキスト分析、翻訳、自然言語処理、感情分析、Q&Aサービス 等
その他	パーソナライズ、コンテンツの推奨、異常検出 当

具体的には、以下のようなサービスが含まれています。

![image](https://github.com/yus04/opc-iot-demo/assets/49590084/b1b90987-7b2f-4082-ac91-b3370647580e)
 
(注釈１)
「Azure AI サービスとは」
https://learn.microsoft.com/ja-jp/azure/ai-services/what-are-ai-services#available-azure-ai-services

	Azure OpenAI Services
Azure OpenAI Services は、OpenAI の高度な人工知能技術を Azure のクラウドプラットフォーム上で利用できるサービスです。

![image](https://github.com/yus04/opc-iot-demo/assets/49590084/a160876b-9db7-48e3-b7fb-a334a41271c9)
 
(Azure OpenAI Service で使用する AI モデルのデプロイやプレイグラウンドでモデル検証を行うための Azure OpenAI Studio の画面。様々なモデルが利用できる。)

Azure OpenAI Service では GPT-4 や GPT-4 omni、GPT-4 Turbo with Vision、Embeddings、DALL-E 3、Whisper などの様々なモデルを利用できるため、自然言語処理や画像認識などの複雑なタスクを容易に実行することができます(注釈１)。例えば、GPT-x モデルを使用してテキスト生成や翻訳、感情分析を行ったり、GPT-4oやGPT-4V の画像認識モデルを利用して画像分類や画像の特徴検出を行うことが可能です(注釈２)。さらに、Azure OpenAI Service は REST API や SDK として提供されているため、簡単にアプリケーションに組み込むことができます。Azure OpenAI Services は、生成 AI を活用したアプリケーション開発において、革新的なソリューションを実現するための重要なツールとなります。

(注釈１)
「Azure OpenAI Service とは」
https://learn.microsoft.com/ja-jp/azure/ai-services/openai/overview
(注釈２)
「Azure OpenAI Service モデル」
https://learn.microsoft.com/ja-jp/azure/ai-services/openai/concepts/models#gpt-4-turbo

	GPT-4 omni モデル
GPT-4 omniは、Azure OpenAI Serviceによって2024年5月に一般提供が開始された最新のマルチモーダルAIモデルです。このモデルは、マルチモーダル性により自然言語、画像、動画を処理できる能力を持ち、画像キャプションの生成やビデオ要約、視覚情報を活用した文章生成などに活用できます。2024年5月現在、GPT-4 omniのバージョンとして、2024-05-13 が利用できます(注釈１)。

(注釈1)
「Azure OpenAI Service モデル」
https://learn.microsoft.com/ja-jp/azure/ai-services/openai/concepts/models#gpt-4-and-gpt-4-turbo-models

	Azure Functions
Azure Functions は、サーバーレスコンピューティングプラットフォームであり、開発者がコードを実行するための環境を提供します(注釈１)。Azure Functions は C＃、JavaScript、Pythonなどの様々な言語やバージョンのランタイムに対応しているため、開発者は自分の技術スタックに合わせた環境でサーバーレスアプリケーションの構築ができます(注釈２)。また、自動スケーリングにも対応しており、開発者はアプリケーションのスケーラビリティやパフォーマンスに気を配ることなく、コードを素早くデプロイし、クラウド上でのアプリケーションの実行ができます(注釈３)。Azure Functions は、トリガーと呼ばれるイベントに反応して実行され、ランタイムで対応している言語で書かれた関数をサポートしています(注釈４)。例えば、HTTP リクエスト、メッセージキューのメッセージ、データベースの更新など、さまざまなトリガーに応じて関数を実行できます。

![image](https://github.com/yus04/opc-iot-demo/assets/49590084/c0a445c2-2ea5-4aa3-b6af-1e74b4f7366f)
 
(注釈５)

これにより、イベント駆動型のアーキテクチャを構築し、柔軟性と効率性を高めることが可能です。Azure Functions は、マイクロサービス、バックエンド処理、IoT デバイスの管理など、さまざまなシナリオで利用され、開発者がアプリケーションを素早く開発し、継続的に改善するための強力なツールとなっています。

(注釈１)
「Azure Functions の概要」
https://learn.microsoft.com/ja-jp/azure/azure-functions/functions-overview?pivots=programming-language-python
(注釈２)
「Azure Functions ランタイム バージョンの概要」
https://learn.microsoft.com/ja-jp/azure/azure-functions/functions-versions?tabs=isolated-process%2Cv4&pivots=programming-language-python
(注釈３)
「Azure Functions のホスティング オプション」
https://learn.microsoft.com/ja-jp/azure/azure-functions/functions-scale
(注釈４)
「Azure Functions でのトリガーとバインドの概念」
https://learn.microsoft.com/ja-jp/azure/azure-functions/functions-triggers-bindings?tabs=isolated-process%2Cpython-v2&pivots=programming-language-python
(注釈５)
「Azure Functions のシナリオ」
https://learn.microsoft.com/ja-jp/azure/azure-functions/functions-scenarios?pivots=programming-language-python

	Azure Blob Storage
Azure Blob Storage は、Microsoft Azure のクラウドストレージサービスであり、大規模なオブジェクトデータを安全に格納、管理、アクセスするための柔軟なソリューションを提供します(注釈１)。ここで、 Blob とは Binary Large Object を意味し、画像、動画、ドキュメントなどの大容量のデータを表します。

![image](https://github.com/yus04/opc-iot-demo/assets/49590084/643e71a3-5481-4c4d-97be-11a924dacefa)
 
(注釈１)
Azure Blob Storage は、データの冗長性と可用性を確保するためのリージョン間レプリケーション(注釈２)や暗号化(注釈３)、アクセスコントロールなどのセキュリティ機能(注釈４)を提供しています。さらに、Azure Blob Storage はスケーラブルでコスト効率の良いストレージオプションを提供し(注釈５)、ニーズに合わせたデータの保存が可能です。

(注釈１)
「Azure Blob Storage の概要」
https://learn.microsoft.com/ja-jp/azure/storage/blobs/storage-blobs-introduction
(注釈２)
「ブロック BLOB のオブジェクト レプリケーション」
https://learn.microsoft.com/ja-jp/azure/storage/blobs/object-replication-overview
(注釈３)
「保存データに対する Azure Storage 暗号化」
https://learn.microsoft.com/ja-jp/azure/storage/common/storage-service-encryption
(注釈４)
「Microsoft Entra ID を使用して BLOB へのアクセスを認可する」
https://learn.microsoft.com/ja-jp/azure/storage/blobs/authorize-access-azure-active-directory
(注釈５)
「BLOB データのアクセス層」
https://learn.microsoft.com/ja-jp/azure/storage/blobs/access-tiers-overview

 
	検索を拡張したインテリジェントアプリの開発
ここから本題である、Azure AI Search と GPT-4 omniを使ってプレゼンテーション資料の検索の拡張をしたインテリジェントアプリの開発について、アーキテクチャの解説、実際のアプリの実装手順、今後の展望について説明します。

	アーキテクチャの解説
アプリケーションのアーキテクチャは下図になり、5 つの Azure サービスを利用しています。
 
 ![image](https://github.com/yus04/opc-iot-demo/assets/49590084/69ffe12e-da98-495e-aa4e-90280a4bb740)

Azure の各サービスの役割と説明について、以下の表にまとめます。

Azure サービス	役割の説明
Azure AI Search	プレゼンテーション資料を高速検索するためのサービス。Azure Blob Storageをデータソースとし、スキルセットやインデクサーを利用することで構造化されたインデックスを作成する。
Azure Blob Storage	Blob を保存するためのサービスであり、Azure AI Search のデータソースとして利用する。GPT-4o に画像としてプロンプトに渡すため、プレゼンテーション資料を jpg 化したデータを保存している。また、デモアプリで検索結果をページごとに表示するため、jpg 化はプレゼンテーション資料のページごとに行っている。
Azure Functions	必要な時にだけ実行可能なサーバーレスのコンピューティングサービス。GPT-4o を使ったドキュメントのエンリッチ化のためのカスタムスキルに利用。
Azure OpenAI Service	GPT-4 omni のモデルをデプロイするためのサービス。GPT-4oではテキスト、画像、動画を入力として受け取り可能なマルチモーダル AI モデル。アプリではプレゼンテーション資料における、図や画像などのイラストの特徴付けや分類を行うために利用。
Azure AI Services	Azure AI Search の組み込みスキルを中規模以上に実行するために必要なサービス。20ドキュメント以内であれば、AI Servicesは必要なくスキルセットを実行することが可能。

また、このアーキテクチャにおいて、インデックスを作成するまでの流れは以下になります。

①	インデクサー実行：インデクサーを実行し、Blob Storage にアップロードされている画像データに対して組み込みのスキルによる OCR や、カスタムスキルによる画像内の図などのイラストの特徴付けや分類を行う。
②	カスタムスキル実行：AI Search のカスタムスキルにより、Azure OpenAI Service にリクエストを投げるための Azure Functions が起動する。
③	カスタムスキル実行：Azure Functions からのリクエストにより、与えられたプロンプトと画像情報を元に、画像内の図などのイラストに対する分析を行う。

さらに、ユーザーがアプリに対して検索をかけて、検索結果が返されるまでの流れは以下になります。

①	検索：ローカル PC に保存されている HTML と JavaScript で書かれたデモアプリに対して、ユーザーがプレゼンテーション資料を行うための検索クエリを入力する。
②	デザイン検索：デモアプリはユーザーに代わって、Azure AI Search に対してデザインの検索を行い、検索結果を受け取る。
③	ファイル取得：検索結果のmetadata_storage_pathから Blob Storage に保存されている画像を取得する。
④	検索結果：AI Search から受け取った検索結果と、Blob Storage から取得した画像データを元に、ユーザーに対して検索結果を表示する。

	実装手順
これらのアプリケーションは Azure ポータルで操作して構築することも可能ですが、本書では Bicep を使って構築することにします。なぜなら、Azure ポータルはUI が定期的に変化し、執筆時点での操作画面と読者の方々の時の操作画面が異なる可能性を懸念したためです。これから、Bicep を使ってアプリケーションをデプロイするための手順について説明します。ただし、注意点として以下からはAzure OpenAI Serviceが利用できる前提で話を進めるため、サブスクリプションに対する申請ができていない場合は次の申請フォームから申請してください。

Request Access to Azure OpenAI Service
https://customervoice.microsoft.com/Pages/ResponsePage.aspx?id=v4j5cvGGr0GRqy180BHbR7en2Ais5pxKtso_Pz4b1_xUNTZBNzRKNlVQSFhZMU9aV09EVzYxWFdORCQlQCN0PWcu

Bicep とは (コラム)
Bicepとは、Azureリソースを管理やデプロイするための言語です(注釈１)。Bicep は Azureのインフラストラクチャをコードで表現する、所謂 IaC (Infrastructure as a Code) です。また、Bicep は全ての Azure リソース と API のバージョンをサポートしている上、JSONベースのARMテンプレートよりも読みやすい特徴があります。このような特徴から、Bicepは Azureリソースのデプロイを行うための強力なツールとして、Azure のクラウドエンジニアに広く受け入れられています。

(注釈１)
「Bicep とは」
https://learn.microsoft.com/ja-jp/azure/azure-resource-manager/bicep/overview?tabs=bicep

本書で扱うサンプルアプリケーションのソースコードが保存されているリポジトリはこちらになります。
https://github.com/yus04/slide-search-app

こちらのリポジトリのコードを使って、サンプルアプリケーションをデプロイする手順については以下の流れになります。

①	環境構築
②	ソースコードのクローン
③	Azure リソースとアプリケーションのデプロイ

それでは、それぞれのステップにて詳細の手順を説明します。

①	環境構築
本書では環境構築のセットアップの手間を省くために、Azure Cloud Shell という Azure 上で利用可能な Shell を利用します。Azure Cloud Shell ではデフォルトで Azure Developer CLI という、Bicep で記述された Azure リソースをデプロイするためのツールや、git などの本書で扱うツールがデフォルトでインストールがされています。

Azure Developer CLI とは (コラム)
Azure Developer CLI とは、アプリケーションをローカル開発環境から Azure に移動させるのを効率的にするツールです(注釈１)。開発者は、アプリの構築、デプロイ、監視、管理などのタスクをAzure Developer CLIを通じて実行できます。Azureのサービスとのやり取りをシンプルにし、自動化やスクリプト化による効率的な作業を可能にします。

(注釈１)
「Azure Developer CLI とは」
https://learn.microsoft.com/ja-jp/azure/developer/azure-developer-cli/overview

Azure Cloud Shell は、ヘッダーにあるターミナルのアイコンを押すことで表示されます(赤枠内のアイコン)。Azure Cloud Shell を使うには Storage Accountが必要なので、作成していない読者の方はこの際に作成をして下さい。
 
![image](https://github.com/yus04/opc-iot-demo/assets/49590084/87969447-e2c8-4b91-ac6d-58f54d02bde1)

(Azure Cloud Shell を起動した様子)

Azure Cloud Shell が起動したことを確認できれば、開発環境のセットアップは終了です。

②	ソースコードのクローン
開発環境のセットアップの次は、ソースコードのクローンを行います。クローンするソースコードは永続的なストレージに保存をするために、Azure Cloud Shell 上で clouddrive ディレクトリに移動してからクローンを実行してください。クローン後、ls コマンドを実行することでクローンしたソースコードを含むフォルダ slide-search-app が表示されます。

cd clouddrive
git clone https://github.com/yus04/slide-search-app
ls

![image](https://github.com/yus04/opc-iot-demo/assets/49590084/8f2c0533-077c-4a81-8118-6478758fdc02)
 
(Azure Cloud Shell で実行した結果)

./src/setupaisearch.sh は azd up 時に実行されるように azure.yaml で定義されているため、chmod コマンドにより、事前にファイルに実行権限を与えます。
cd slide-search-pp
chmod +x src/setupaisearch.sh

![image](https://github.com/yus04/opc-iot-demo/assets/49590084/657b367a-2cf2-4ef0-87ef-dbcf20efda36) 

補足：setupaisearch.sh への実行権限の付与について
Azure Cloud Shell でソースコードをクローンした状態で ls -lh src/setupaisearch.sh を実行すると確認できますが、今回のケースでは setupaisearch.sh にもともと実行権限が付与されているため、chmod コマンドを実行する必要はありません。
 
 ![image](https://github.com/yus04/opc-iot-demo/assets/49590084/62b4b0f7-29bf-491f-8209-71a604cb362b)

③	Azureリソースとアプリケーションのデプロイ
azd up でAzure リソースの作成とアプリケーションのデプロイをしていきます。
azd up
まず、「Enter a new environment name」 と言われるので、環境名を入力します。これはリソースグループ名にもなるため、既存のリソースグループ名と重複が無いように決定します。また、「Select an Azure Subscription to use」と言われるので、利用する Azure サブスクリプションを選択したあと、「Select an Azure location to use」と言われるので、Azureリソースを作成するリージョンを決定します。infra/main.bicep を確認すると確認できますが、GPT-4o だけは GA されている eastus で固定にしておりますので、お好きなリージョンを選択ください。特にこだわりが無ければ東日本リージョン (japaneast) にします。すると、以下の画面のようにAzureリソースのプロビジョニングが開始します。

![image](https://github.com/yus04/opc-iot-demo/assets/49590084/61d3d3cb-bdc3-4447-a2b4-b3860946434b)
 
(azd up を実行した後にいくつかの質問事項に回答し、Azureリソースのプロビジョニングが開始している様子)
デプロイには10~15 分程度の時間がかりますが、最終的にはデプロイが完了し、以下の画面のような画面が表示されます。

![image](https://github.com/yus04/opc-iot-demo/assets/49590084/9eba88f0-96e9-4364-95db-e90f5b96bfe0)
 

無事、デプロイ完了の画面が表示されたらAzure ポータルを確認して、必要な Azure リソースや AI Search のデータソース、インデックス、スキルセット、インデクサー、が作成されていることを確認します。サンプルアプリのドキュメントは65つあるため、インデックスのドキュメント数が65になっていればデプロイは成功です。

![image](https://github.com/yus04/opc-iot-demo/assets/49590084/f2eb16d8-fd91-4978-957e-e36444b288c9) 

![image](https://github.com/yus04/opc-iot-demo/assets/49590084/a5a5b50e-7c87-42af-91ac-950bdcfba3ad)

![image](https://github.com/yus04/opc-iot-demo/assets/49590084/dbdc1ced-bb76-43ad-9710-16420b9ea78f)

	利用方法
それでは、デプロイしたアプリケーションを利用していきます。最初にAzure ポータルで作成済みのAzure AI Search を選択します。その次に、左側のメニューバーにある「インデックス」を選択し、「slide-search-app-index」を押します。

![image](https://github.com/yus04/opc-iot-demo/assets/49590084/636fff3d-132b-40ca-a3c0-0003e6e30185)
 
上のタブに「デモアプリの作成」があるので、選択したあとモーダルで表示される「CORSを有効にして実行する」を押します。

![image](https://github.com/yus04/opc-iot-demo/assets/49590084/7b3a27eb-d633-45d5-985a-33be0f22aa33)
 
この画面では、個々の結果のカスタマイズをしていきます。縮小版には「metadata_storage_path」を選択し、タイトルには「metadata_storage_name」を選択し、説明には「explaination」を選んだ上で「次へ」を押します。

![image](https://github.com/yus04/opc-iot-demo/assets/49590084/2bfaaed0-a612-47ab-a1fe-54c2d63bcbe4)
 
サイドバーはカスタマイズ不要なのでそのまま「次へ」を押します。
 
![image](https://github.com/yus04/opc-iot-demo/assets/49590084/f39011b8-15a6-448f-97fc-9fda2538913a)

候補のカスタマイズも不要なので、そのまま「デモアプリの作成」を行います。

![image](https://github.com/yus04/opc-iot-demo/assets/49590084/c921e2ea-9bb8-438b-9e93-390d485bac0e)

デモアプリの準備が完了したら、「ダウンロード」を押します。
 
![image](https://github.com/yus04/opc-iot-demo/assets/49590084/126eb444-c3e5-4b2e-86fa-e299ae4dd63e)

エクスプローラーのダウンロードを見るとAzSearchというファイルがあるので、選択する。

![image](https://github.com/yus04/opc-iot-demo/assets/49590084/060da3a2-5f14-422e-bc29-c5149bec93be)

以下のような画面が表示される。
 
![image](https://github.com/yus04/opc-iot-demo/assets/49590084/ed8e2f10-f29a-4f45-b0a7-b3f530a01013)

検索バーの右にある虫眼鏡のアイコンを選択すると、インデックスに登録されているプレゼンテーション資料の一覧が表示されれば、無事デモアプリの作成は成功です。
 
![image](https://github.com/yus04/opc-iot-demo/assets/49590084/144380bd-6ec4-4800-bdd0-e2d1fc72b140)

	デモアプリを使った検索
「人」のイラストが載っている資料の検索
 
 ![image](https://github.com/yus04/opc-iot-demo/assets/49590084/f86c5d30-eba3-426d-9205-2a2ba0040c12)

「フロー図」で書かれた資料の検索
 
![image](https://github.com/yus04/opc-iot-demo/assets/49590084/b27fcbf4-c602-4756-9793-9ec7ddb610a9)

「JISEC」の企業ロゴが載っている資料の検索
 
 ![image](https://github.com/yus04/opc-iot-demo/assets/49590084/d4fc95fb-dc82-4579-ad88-7de31541fef5)

「ビル」の写真を含む資料の検索
 
![image](https://github.com/yus04/opc-iot-demo/assets/49590084/173916da-58ca-4cfb-9d42-bc175aad7ca6)

	サンプルアプリの解説
	プロンプトの解説
サンプルアプリのリポジトリ(https://github.com/yus04/slide-search-app)にあるファイルにも書かれていますが、GPT-4oに渡しているプロンプトは以下のものになります。

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

GPT-4oのモデルは json モードの対象外のため(注釈１)、回答はjson形式になるようプロンプトで指示を与えています。

 ![image](https://github.com/yus04/opc-iot-demo/assets/49590084/a2e877be-f574-4d04-abb2-a75223eb2b0f)

(注釈１)
「JSON モードを使用する方法について説明します」
https://learn.microsoft.com/ja-jp/azure/ai-services/openai/how-to/json-mode?tabs=python#json-mode-support

	インデックスの解説
AI Search のインデックスを検索してみると確認できますが、インデックスのスキーマは以下のものになっています。
 
![image](https://github.com/yus04/opc-iot-demo/assets/49590084/baf5f3fa-4870-471c-9b1a-1fcb497386e6)

text	スライド内の文章
explanation	50 文字程度のスライドの説明
illustration	図の説明
photo	写真の中にある物
design	デザインの分類
logo	企業ロゴ

textはAI Servicesの組み込みスキルによるものですが、それ以外のフィールドについてはGPT-4oによってエンリッチされた情報になります。

	今後の展望
今後の展望として、簡単にサンプルアプリの課題について説明します。まず、インデクサーの実行時間が長くなる傾向にあります。従量課金で実行する場合は、レスポンスが遅くなる場合がありますし、ドキュメント数が増えると更にインデクサーの実行に時間がかかります。サンプルアプリの実行時間は約10分になっています。

![image](https://github.com/yus04/opc-iot-demo/assets/49590084/b628cf08-cbb4-45a6-b9a2-e522672744a5)

また、GPT-4oとは関係ありませんが、AI Searchでベクトル検索を使っていないため、GPT-4oによって出力されたキーワードと一致したキーワードで検索をかけないと、検索結果に出力されません。例えば、本、書籍と書籍はほぼ同じ意味を示す用語ですが、サンプルアプリでは区別して扱われています。

	終わりに
本書では、Azureサービスの紹介をした後、インテリジェントアプリのデプロイ方法から利用方法、プロンプトやインデックスの解説、今後の展望についてまとめました。プロンプトの調整などはまだまだ必要になりますが、実際にGPT-4oを使ってみて、プレゼンテーション資料の検索の拡張が可能になりました。今後は、プロンプトの調整やインデックスの最適化など、さらなる改善が求められますが、これによってユーザーはよりスムーズに期待しているプレゼンテーション資料の検索の実現が期待できます。最後に、AI技術の発展によりより洗練された検索精度になることを期待しています。

執筆者プロフィール
・齊藤優：大学院でバイオインフォマティクス分野での研究をした後、IT企業に入社し、Azureを使った仕事をしています。好きなAzureサービスは App Service, AI Search, Logic Apps です。
