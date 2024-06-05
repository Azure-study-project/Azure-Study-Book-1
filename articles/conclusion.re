= まとめ

== 今後の展望

今後の展望として、簡単にサンプルアプリの課題について説明します。まず、インデクサーの実行時間が長くなる傾向にあります。従量課金で実行する場合は、レスポンスが遅くなる場合がありますし、ドキュメント数が増えると更にインデクサーの実行に時間がかかります。サンプルアプリの実行時間は約10分になっています。

//image[fin][サンプルアプリの実行時間][scale=1.0]{
//}

また、GPT-4oとは関係ありませんが、AI Searchでベクトル検索を使っていないため、GPT-4oによって出力されたキーワードと一致したキーワードで検索をかけないと、検索結果に出力されません。例えば、本、書籍と書籍はほぼ同じ意味を示す用語ですが、サンプルアプリでは区別して扱われています。

== 終わりに

本書では、Azureサービスの紹介をした後、インテリジェントアプリのデプロイ方法から利用方法、プロンプトやインデックスの解説、今後の展望についてまとめました。プロンプトの調整などはまだまだ必要になりますが、実際にGPT-4oを使ってみて、プレゼンテーション資料の検索の拡張が可能になりました。今後は、プロンプトの調整やインデックスの最適化など、さらなる改善が求められますが、これによってユーザーはよりスムーズに期待しているプレゼンテーション資料の検索の実現が期待できます。最後に、AI技術の発展によりより洗練された検索精度になることを期待しています。