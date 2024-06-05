= Azure AI Search と GPT-4 omni を使ったプレゼンテーション資料の検索を拡張したインテリジェントアプリの開発

== はじめに

この技術書は、2024年5月現在でGPTの最新モデルであるGPT-4 omni (GPT-4o)を使ったユースケースとして、プレゼンテーション資料の検索を拡張したインテリジェントアプリの開発について述べています。GPT-4oはテキスト、画像、動画、音声を入出力できるマルチモーダルなモデルであり、本技術書の例では、テキストと画像を入力と受け取ることで従来のテキストのみによる資料検索の拡張を図っています。

プレゼンテーション資料の検索を行いたい場合、Microsoftのエコシステムの中に限っても資料を探す方法は多岐にわたります。例えば、Bingでは職場向けの検索ができ、検索に関連するWord、PowerPoint、SharePoint等の資料を探しだすことができます。Copilotを利用した社内文書検索では、CopilotやMicrosoft 365 CopilotがMicrosoft Graph APIを介してアクセスできるファイルの中から関連する資料を検索し、ドキュメントを得ることができます。

また、SharePointのような社内のポータルサイトやTeamsによるコミュニケーションアプリ、Outlookなどのメールを通じた検索方法も一般的です。しかし、これらの従来の検索方法にはいくつかの制限があります。例えば、テキスト以外の情報を含む資料や、資料に含まれる図や画像に関する情報を利用した検索が困難です。現状では、テキスト情報に依存しており、テキスト以外の情報を持つ資料に対する検索精度や効率性に課題があります。

そこで、これらの限界を克服し、プレゼンテーション資料の検索を拡張するためには、新たなアプローチが必要です。まず、GPT-4oの画像認識技術や自然言語処理技術を活用して、資料内の図や画像に対する検索機能を強化することが考えられます。これにより、テキスト以外の情報を含む資料に対する検索の精度と効率性を向上させることができます。さらに、資料のメタデータやタグ付けを活用して、テキスト以外の情報も含めた効果的な検索を実現することが重要です。これにより、資料の属性や特徴に基づいた高度な検索が可能になります。

このように、新たな技術とアプローチを活用することで、従来のプレゼンテーション資料の検索方法の限界を克服し、より効率的で精度の高い検索体験を提供することが可能になり、これにより、組織内の知識共有や情報アクセスが向上し、業務効率の向上に貢献します。

本技術書では、上記にある新しいアプローチを提案する内容になっています。また、提案では様々なAzureサービスを利用していますが、それぞれの製品に対する説明をしているため、Azure初学者の方でも理解しやすい内容になっています。この本ではGPT-4oでデプロイしたインテリジェントアプリを手軽に試せるようにテンプレート化しており、実際にご自身の環境で動かすことで簡単にGPT-4oの威力をご体感頂けます。そして、最終的には読者がGPT-4oを活用したインテリジェントアプリの開発に自信を持ち、実際のプロジェクトやビジネスに応用できるようになることをゴールとしています。
