# 姿勢シミュレータ仕様書～ヒッパルコス星表～

## 1.  概要
- csv形式のヒッパルコス星表のデータを読み取り，他クラスで使用できるようにするためのクラス．
- `sample_simulation_base.ini` によりあらかじめ読み出す視等級の上限を決める．
### 1. 関数
+ `ReadContents`
  * `hip_main.csv`を読み出してデータに格納する関数．
+ 各種 `Get` 関数
  * クラス外から `HipparcosCatalogue` のデータにアクセスする場合に用いる関数．

### 2. 関連ソースコード，ファイル
+ `HipparcosCatalogue.cpp` ，`HipparcosCatalogue.hpp`
  * クラスの定義が行われている．
+ `initialize_global_environment.cpp`
  * 初期化関数が記述されている
+ `sample_simulation_base.ini`
  * 初期化ファイル
+ `hip_main.csv`
  * ヒッパルコス星表の元データ． `s2e-core` 外の `ExtLibraries`  に保存される．使用しやすいように，HIP ID順ではなく，視等級の小さい順にソートされている．

### 3. 外部ライブラリのダウンロードに関して
+ まずは`hip_main.csv` のダウンロードを済ませる必要がある．このためのスクリプトとして `s2e-core/scripts/download_HIPcatalogue.sh`を用意した．Git Bashなどを利用して，このスクリプトがあるディレクトリで以下を実行することで，必要なcsvファイルをダウンロードすることができる．
  * Macユーザーは，Mac標準のターミナルからではなく，Docker内のUbuntuのターミナルから実行する必要がある．（ `sed` の仕様がMacとLinuxで違うので，正しいcsvファイルを生成することができないため．参考：<https://qiita.com/catfist/items/1156ae0c7875f61417ee>）
```
bash download_HIPcatalogue.sh 
``` 

### 4. 使い方
+ `sample_simulation_base.ini`でパラメータを設定
+ 初期化関数 `InitHipparcosCatalogue` を利用し，インスタンスを生成
+ `GetContents` を実行することで，csvファイルからデータを取得する．
+ 各種情報が必要な場合は， `Get` 関数を使って取得する．
+ hipparcos_id（HIP ID），visible_magnitude（視等級），right_ascension_deg（赤経），declination_deg（赤緯）の4要素を持つ `HipparcosData` 構造体を定義している．データはこの `HipparcosData` 型を要素にとるベクタとして保存される．

## 2. アルゴリズム説明

## 3. 動作確認結果
ヒッパルコス星表のデータを用いた動作確認を `Spec_Telescope.md` にて行っているため，その結果を動作確認結果とする．


