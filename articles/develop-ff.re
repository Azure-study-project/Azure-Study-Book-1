== 4.3 開発環境の準備

Azure App Service にデプロイする前に、ローカル環境で Streamlit アプリケーションを開発・実行するための準備を行いましょう。

 1. @<b>{リポジトリのクローン:}

//beginchild

//emlist[][bash]{
git clone https://github.com/Azure-study-project/search_app_front.git
cd search_app_front
//}

上記のコマンドを実行して、サンプルアプリケーションのリポジトリをクローンし、作業ディレクトリに移動します。

//endchild

 2. @<b>{Python 仮想環境の作成:}

//beginchild

//emlist[][bash]{
python -m venv venv
//}

Python の仮想環境を作成します。仮想環境を使うことで、プロジェクトごとに必要なライブラリを独立して管理できます。

//endchild

 3. @<b>{仮想環境のアクティベート:}

//beginchild

//emlist[][bash]{
source venv/bin/activate  # macOS/Linux
venv\Scripts\activate     # Windows
//}

作成した仮想環境をアクティベートします。ターミナルのプロンプトに @<tt>{(venv)} が表示されれば、アクティベート成功です。

//endchild

 4. @<b>{必要なライブラリのインストール:}

//beginchild

//emlist[][bash]{
pip install -r requirements.txt
//}

@<tt>{requirements.txt} に記載されている必要なライブラリをインストールします。

//endchild

 5. @<b>{環境変数の設定}:

//beginchild

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

 * @<tt>{AZURE_SEARCH_ENDPOINT}: Azure AI Search のエンドポイント（例: @<tt>{https://[your_search_service_name].search.windows.net}）
 * @<tt>{AZURE_SEARCH_API_KEY}: Azure AI Search の管理 API キー
 * @<tt>{AZURE_SEARCH_INDEX_NAME}: 作成したインデックスの名前

//endchild

 6. @<b>{アプリケーションの起動:}

//beginchild

//emlist[][bash]{
streamlit run Top.py
//}

上記のコマンドを実行すると、Streamlit アプリケーションが起動し、ブラウザで @<tt>{http://localhost:8501} にアクセスすることで、開発中のアプリケーションを確認できます。

//endchild
