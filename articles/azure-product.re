= Azure 製品紹介

== Azure AI Search

=== Azure AI Search とは

Azure AI Search (旧称：Azure Cognitive Search) は、Azure のクラウドプラットフォーム上で提供される、高度な検索ソリューションです。@<fn>{azure_search_intro}このサービスを利用することで、豊富なデータセットからの効率的な情報検索を実現できます。

//image[ai_search][AI Search とは][scale=1.0]{
//}

Azure AI Search はセマンティックランク付けによって、テキストベースでのクエリに対して、検索結果の精度やパフォーマンスを向上させます。@<fn>{semantic_ranking}また、インデクサーによって自動化されたインデックス作成や、組み込みスキルによるインデックス情報のエンリッチ化、カスタムスキルによる高度なスキル構築など、多彩な機能を提供します。@<fn>{search_features_list}そのため、Azure AI Search は、電子商取引プラットフォーム、コンテンツ管理システム、カスタマーサポートポータル、教育機関の資料検索システムなど、様々なプラットフォームにて情報検索機能の強化のために活用されています。

//footnote[azure_search_intro][Azure AI Search とは, https://learn.microsoft.com/ja-jp/azure/search/search-what-is-azure-search]
//footnote[semantic_ranking][Azure AI Search でのセマンティック ランク付け, https://learn.microsoft.com/ja-jp/azure/search/semantic-search-overview]
//footnote[search_features_list][Azure AI Search の機能, https://learn.microsoft.com/ja-jp/azure/search/search-features-list]

=== Azure AI Search の主要機能

ここでは、Azure AI Search を使った検索システムを構築する上で、必ず知っておかないといけない主要機能について簡単に解説します。

==== データソース

データソースとは、検索対象となるデータの元となるリソースやデータストアのことを指し、検索エンジンがインデックス化するデータの情報源となるものです。具体的には、Azure SQL Database、Azure Cosmos DB などのデータベースや、Azure Table Storage、Azure Blob Storage といったストレージ、SharePoint やサードパーティーのサービスをデータソースとして利用することができます。

//image[datasouce][データソースの例][scale=1.0]{
//}
@<fn>{data_sources_gallery}

Azure AI Search では、これらのデータソースからデータを取得し、利用可能な形式に変換してインデックスに格納することで、ユーザーが高速で効率的な検索を実行できるようになります。

//footnote[data_sources_gallery][データ ソース ギャラリー, https://learn.microsoft.com/ja-jp/azure/search/search-data-sources-gallery]

==== インデックス

インデックスとは、検索エンジンがデータを効率的に検索可能な形式で格納するための構造化されたデータの集合を指します@<fn>{search_index}。検索対象となるデータソースのデータをコピーして構造化しておくことで、検索クエリの高速な実行や結果の取得を支援します。インデックスには、フィールドと呼ばれる、データの特定の属性やカテゴリを表すフィールドを含んでいます。フィールドの例には、製品名、価格、カテゴリなどがあります。インデックスは、Azure AI Search が提供する検索機能を活用するための中心的なコンポーネントであり、データの高速な検索や検索結果の適切な表示を実現する上で重要な役割を果たします。

//footnote[search_index][Azure AI Search の検索インデックス, https://learn.microsoft.com/ja-jp/azure/search/search-what-is-an-index]

==== スキルセット

スキルセットとは、テキストや画像などのコンテンツを解析し、その情報を構造化するための一連の処理ステップのことであり、よりリッチなインデックスを構築するためにドキュメントをエンリッチするために使用されます。

//image[skillset][スキルセットの例][scale=1.0]{
//}
@<fn>{skillsets}

Azure AI Search の組み込みのスキルセットには、テキストデータに対するスキルセットとして、テキスト解析、キーフレーズ抽出、エンティティ抽出、言語検出などの処理を行うスキルや、画像に対するスキルセットとして、オブジェクト検出、顔検出、画像の特徴量抽出などの処理を行うスキルセットがあります@<fn>{predefined_skills}。このように、スキルセットは Azure AI Search が効果的にコンテンツを理解して、検索、分析、等の操作を行うための補助を行う機能です。ただし、組み込みのスキルは限られた数のドキュメントしか無料でエンリッチすることができないので、基本的には後述する Azure AI Services のリソースをアタッチする必要があります@<fn>{attach_cognitive_services}。

//footnote[skillsets][Azure AI Searchでのスキルセットの概念, https://learn.microsoft.com/ja-jp/azure/search/cognitive-search-working-with-skillsets]
//footnote[predefined_skills][インデックス付け中に追加処理を行うスキル (Azure AI Search), https://learn.microsoft.com/ja-jp/azure/search/cognitive-search-predefined-skills]
//footnote[attach_cognitive_services][Azure AI マルチサービス リソースを Azure AI Search のスキルセットにアタッチする, https://learn.microsoft.com/ja-jp/azure/search/cognitive-search-attach-cognitive-services?tabs=portal%2Cportal-remove]

==== カスタムスキル

スキルセットに関連して、カスタムスキルという、ユーザーが独自の処理ロジックを組み込んだスキルがあります。通常、Azure AI Search では、テキストや画像などのコンテンツに対する組み込みスキルを提供していますが、特定の要件や高度な要求に対応するためには、これらのスキルだけでは不十分です。そのような場合に使われるのがカスタムスキルであり、スキルの柔軟性や拡張性を高めることができます。カスタムスキルはの一般的なホスティング先としては、Azure Functions やコンテナーになります@<fn>{custom_skill}。

//footnote[custom_skill][Azure AI Search エンリッチメント パイプラインにカスタム スキルを追加する, https://learn.microsoft.com/ja-jp/azure/search/cognitive-search-custom-skill-interface]

カスタムスキルを構築し、Azure AI Search のパイプラインに組み込むことで、独自の処理を適用できます。

例えば、テキストデータに対するカスタムスキルを作成することで、特定のテキストパターンの検出、カスタム言語モデルの適用、特定のエンティティの抽出などを行うことができます。また、画像データに対するカスタムスキルを作成することで、特定のオブジェクトの識別、カスタムフィルタリング、画像の特徴量抽出などを行うことができます。

カスタムスキルは、Azure Cognitive Search の柔軟性と拡張性を高め、ユーザーが特定の要件に応じて検索や分析を行う能力を向上させます。

==== インデクサー

インデクサーはデータソースからデータを取得し、検索可能な形式に変換して自動的にインデックスに格納する機能を指します。インデクサーは、以下のようなフローでそれぞれのタスクを実行します。

//image[indexer][インデクサーのフローチャート][scale=1.0]{
//}
@<fn>{indexer_stage}

 * ステージ１ (ドキュメント解析)：インデクサーはまず最初に、データベースや Blob ストレージなどの様々なデータソースに対して、テキストや画像、メタデータなどのデータを取得します。

 * ステージ２ (フィールドマッピング)：インデクサーは次に、取得したデータを検索エンジンで効率的に検索できる形式に変換するために、データのフィールドのマッピングを実施します。

 * ステージ3 (スキルセットの実行)：そして、インデクサーはスキルセットが定義されていた場合は、インデックスをエンリッチ化するためにスキルセットを実行します。スキルセットには、OCR や 翻訳、テキスト分割、画像分析などの組み込みのスキルや、カスタムスキルを用いて独自にスキルセットを構築することができます。

 * ステージ４ (出力フィールドマッピング)：さらに、スキルセットが定義されておりドキュメントのエンリッチ化が行われた場合には、インデクサーはエンリッチされたドキュメントを検索可能な形式に変換するために、データの出力フィールドマッピングを実施します。

 * ステージ5 (インデックスへの格納)：最後にインデクサーは、マッピングされたデータをインデックスに格納します。

また、インデクサーは上記のステージ１からステージ５を定期的に実行することで、データソースからの新しいデータや変更されたデータからインデックスを更新します。これにより、検索エンジンが最新の情報を提供できるようになります。

//footnote[indexer_stage][インデックス作成のステージ, https://learn.microsoft.com/ja-jp/azure/search/search-indexer-overview#stages-of-indexing]

== Azure AI Services

Azure AI Services は、クラウドベースの AI サービスのセットです。これらのサービスは、企業や開発者が AI 機能をアプリケーションに統合することを容易にするために設計されており、以下のような主要な機能を提供しています。@<fn>{what_are_ai_services}

//table{
機能	説明
--------------
分析サービス	画像と動画の分析、物体検出、顔認識、文字認識（OCR）等
音声サービス	音声認識、音声合成、音声翻訳、スピーカー認識 等
言語サービス	テキスト分析、翻訳、自然言語処理、感情分析、Q&A サービス 等
その他	パーソナライズ、コンテンツの推奨、異常検出 等
//}

具体的には、以下のようなサービスが含まれています。

//image[azure_ai_services][Azure AI Services の例][scale=1.0]{
//}

//footnote[what_are_ai_services][Azure AI サービスとは, https://learn.microsoft.com/ja-jp/azure/ai-services/what-are-ai-services#available-azure-ai-services]

== Azure OpenAI Services

Azure OpenAI Services は、OpenAI の高度な人工知能技術を Azure のクラウドプラットフォーム上で利用できるサービスです。

//image[azure_openai_services][Azure OpenAI Services の例][scale=1.0]{
//}

Azure OpenAI Service では GPT-4 や GPT-4 omni、GPT-4 Turbo with Vision、Embeddings、DALL-E 3、Whisper などの様々なモデルを利用できるため、自然言語処理や画像認識などの複雑なタスクを容易に実行することができます。@<fn>{azure_openai_service_overview} 例えば、GPT-x モデルを使用してテキスト生成や翻訳、感情分析を行ったり、GPT-4o や GPT-4V の画像認識モデルを利用して画像分類や画像の特徴検出を行うことが可能です。@<fn>{azure_openai_service_models} さらに、Azure OpenAI Service は REST API や SDK として提供されているため、簡単にアプリケーションに組み込むことができます。Azure OpenAI Services は、生成 AI を活用したアプリケーション開発において、革新的なソリューションを実現するための重要なツールとなります。

//footnote[azure_openai_service_overview][Azure OpenAI Service とは, https://learn.microsoft.com/ja-jp/azure/ai-services/openai/overview]
//footnote[azure_openai_service_models][Azure OpenAI Service モデル, https://learn.microsoft.com/ja-jp/azure/ai-services/openai/concepts/models#gpt-4-and-gpt-4-turbo-models]

== GPT-4 omni モデル

GPT-4 omni は、Azure OpenAI Service によって 2024 年 5 月に一般提供が開始された最新のマルチモーダル AI モデルです。このモデルは、マルチモーダル性により自然言語、画像、動画を処理できる能力を持ち、画像キャプションの生成やビデオ要約、視覚情報を活用した文章生成などに活用できます。2024 年 5 月現在、GPT-4 omni のバージョンとして、2024-05-13 が利用できます。@<fn>{azure_openai_service_models2}

//footnote[azure_openai_service_models2][Azure OpenAI Service モデル, https://learn.microsoft.com/ja-jp/azure/ai-services/openai/concepts/models#gpt-4-and-gpt-4-turbo-models]

== Azure Functions

Azure Functions は、サーバーレスコンピューティングプラットフォームであり、開発者がコードを実行するための環境を提供します。@<fn>{azure_functions_overview} Azure Functions は C#、JavaScript、Python などの様々な言語やバージョンのランタイムに対応しているため、開発者は自分の技術スタックに合わせた環境でサーバーレスアプリケーションの構築ができます。@<fn>{azure_functions_versions} また、自動スケーリングにも対応しており、開発者はアプリケーションのスケーラビリティやパフォーマンスに気を配ることなく、コードを素早くデプロイし、クラウド上でのアプリケーションの実行ができます。@<fn>{azure_functions_hosting_options} Azure Functions は、トリガーと呼ばれるイベントに反応して実行され、ランタイムで対応している言語で書かれた関数をサポートしています。@<fn>{azure_functions_triggers_bindings} 例えば、HTTP リクエスト、メッセージキューのメッセージ、データベースの更新など、さまざまなトリガーに応じて関数を実行できます。

//image[azure_functions][Azure Functions の例][scale=1.0]{
//}

これにより、イベント駆動型のアーキテクチャを構築し、柔軟性と効率性を高めることが可能です。Azure Functions は、マイクロサービス、バックエンド処理、IoT デバイスの管理など、さまざまなシナリオで利用され、開発者がアプリケーションを素早く開発し、継続的に改善するための強力なツールとなっています。@<fn>{azure_functions_scenarios}

//footnote[azure_functions_overview][Azure Functions の概要, https://learn.microsoft.com/ja-jp/azure/azure-functions/functions-overview?pivots=programming-language-python]
//footnote[azure_functions_versions][Azure Functions ランタイム バージョンの概要, https://learn.microsoft.com/ja-jp/azure/azure-functions/functions-versions?tabs=isolated-process%2Cv4&pivots=programming-language-python]
//footnote[azure_functions_hosting_options][Azure Functions のホスティング オプション, https://learn.microsoft.com/ja-jp/azure/azure-functions/functions-scale]
//footnote[azure_functions_triggers_bindings][Azure Functions でのトリガーとバインドの概念, https://learn.microsoft.com/ja-jp/azure/azure-functions/functions-triggers-bindings?tabs=isolated-process%2Cpython-v2&pivots=programming-language-python]
//footnote[azure_functions_scenarios][Azure Functions のシナリオ, https://learn.microsoft.com/ja-jp/azure/azure-functions/functions-scenarios?pivots=programming-language-python]

== Azure Blob Storage

Azure Blob Storage は、Microsoft Azure のクラウドストレージサービスであり、大規模なオブジェクトデータを安全に格納、管理、アクセスするための柔軟なソリューションを提供します。@<fn>{azure_blob_storage_introduction} ここで、Blob とは Binary Large Object を意味し、画像、動画、ドキュメントなどの大容量のデータを表します。

//image[azure_blob_storage][Azure Blob Storage の例][scale=1.0]{
//}

Azure Blob Storage は、データの冗長性と可用性を確保するためのリージョン間レプリケーション@<fn>{block_blob_object_replication}や暗号化@<fn>{azure_storage_encryption}、アクセスコントロールなどのセキュリティ機能@<fn>{authorize_access_azure_active_directory}を提供しています。さらに、Azure Blob Storage はスケーラブルでコスト効率の良いストレージオプションを提供し@<fn>{blob_data_access_tiers}、ニーズに合わせたデータの保存が可能です。

//footnote[azure_blob_storage_introduction][Azure Blob Storage の概要, https://learn.microsoft.com/ja-jp/azure/storage/blobs/storage-blobs-introduction]
//footnote[block_blob_object_replication][ブロック BLOB のオブジェクト レプリケーション, https://learn.microsoft.com/ja-jp/azure/storage/blobs/object-replication-overview]
//footnote[azure_storage_encryption][保存データに対する Azure Storage 暗号化, https://learn.microsoft.com/ja-jp/azure/storage/common/storage-service-encryption]
//footnote[authorize_access_azure_active_directory][Microsoft Entra ID を使用して BLOB へのアクセスを認可する, https://learn.microsoft.com/ja-jp/azure/storage/blobs/authorize-access-azure-active-directory]
//footnote[blob_data_access_tiers][BLOB データのアクセス層, https://learn.microsoft.com/ja-jp/azure/storage/blobs/access-tiers-overview]
