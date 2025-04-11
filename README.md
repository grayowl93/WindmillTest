# WindmillTest  
移動体の中心を主成分分析で求める  
  
胴体検出のテスト  
対象を風車のブレードとする  
入力された動画からコマを取り出し、移動する領域の主成分分析を行う  
  
# フォルダ構成  
```txt:  
┣WindmillTest					//プロジェクトルート  
┃　┣res						//リソースフォルダー  
┃　┣WindmillTest.ico			//アイコン  
┃　┗WindmillTest.rc2			//手入力GUIリソース（空）  
┣framework.h					//フレームワークバージョン指定ヘッダーファイル  
┣pch.cpp						//プリコンパイル済みソース本体  
┣pch.h							//プリコンパイル済みヘッダーファイル  
┣resource.h					//リソース通し番号定義ヘッダーファイル  
┣WindmillTest.cpp				//アプリケーション本体ソース本体  
┣WindmillTest.h				//アプリケーション本体ヘッダーファイル  
┣WindmillTest.rc				//リソースGUI定義ファイル  
┣WindmillTestDlg.cpp			//GUI本体ソース本体  
┣WindmillTestDlg.h				//GUI本体ヘッダーファイル  
┣targetver.h					//Windoswターゲットバージョン指定ヘッダーファイル  
┣UserCommon.h					//共通インクルードファイル  
┣WindmillTest.vcxproj			//プロジェクト ファイル  
┣WindmillTest.vcxproj.filters	//ソリューションに追加されたファイルを配置する場所を指定  
┣WindmillTest.vcxproj.user		//別バージョンのVisualStudioから移行ユーザー ファイル  
┣WindmillTest.sln				//VisualStudioソリューションファイル  
┗README.md						//本READMEファイル  
```  
  
# 利用オープンソース  
* Eigen  
Eigenはヘッダーのみで提供されるテンプレートライブラリです。  
線形代数の演算を高速で実行できます。  
https://eigen.tuxfamily.org/index.php?title=Main_Page  
  
* Eigenインストール方法  
  
Windows  
　自分で直接管理する場合  
１．eigen-3.4.0.zipをダウンロード解凍する。  
２．\eigen-3.4.0\eigen-3.4.0\Eigenを、自身のPCのローカル上に置く。  
３．VisualStudioのインクルードパスに、上記フォルダーを追加する。  
  
　vcpkgを使う場合（VisualStudioの環境設定をしてくれるのでお勧め）  
１．vcpkgをインストールする。  
２．コマンドプロンプトを管理者として実行、以下のコマンドを実行する。  
c:\vcpkg\vcpkg search eigen  
c:\vcpkg\vcpkg install eigen3:x64-windows  
３．システムの環境変数Pahtに、次を追加する。  
　c:\vcpkg\installed\x64-windows\bin  
  
Linux　Debian系  
$ sudo apt install -y libeigen3-dev  
  
Linux　RedHat系  
$ dnf -y install eigen3-devel  
  
* OpenCV  
　各自、OpenCVからダウンロードして、ローカルPCに配置する。  
https://opencv.org/  
  
注）OpenCVのデバックモードライブラリは、メモリーリークを起こしている。  
OpenCV自体のデバックはしないので、リリースモードライブラリを、デバック/リリース双方で使用することを奨励する。  
  
# ビルド方法  
* WindmillTest  
　VisualStudioから立ち上げる場合、WindmillTest.slnファイルをダブルクリックでプロジェクトを開く。  
  
# 初回のgitコマンドでエラーが出た場合  
エラーメッセージにある、git configを実行します。  
１．コマンドプロンプトを管理者として開く。  
２．自身のローカル環境のフォルダーパスを指定してgit configを実行します。  
＜＜＜注意＞＞＞  
　フォルダーパスは、シングルコーテーションを取り除きます。  
誤：git config --global --add safe.directory 'F:/mywork'  
正：git config --global --add safe.directory F:/mywork  
  
# コマンドラインから新しいリポジトリを作成  
touch README.md  
git init  
git checkout -b main  
git add README.md  
git commit -m "first commit"  
git remote add origin https://youkan-ogura.nikonoa.net/DLR-ZT/WindmillTest.git  
git push -u origin main  
# コマンドラインから既存のリポジトリをプッシュ  
git remote add origin https://youkan-ogura.nikonoa.net/DLR-ZT/WindmillTest.git  
git push -u origin main  
  
