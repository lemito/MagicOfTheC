# How run test inside project?

## For ubuntu

* Install bazel
```bash
sudo apt install apt-transport-https curl gnupg -y
curl -fsSL https://bazel.build/bazel-release.pub.gpg | gpg --dearmor >bazel-archive-keyring.gpg
sudo mv bazel-archive-keyring.gpg /usr/share/keyrings
echo "deb [arch=amd64 signed-by=/usr/share/keyrings/bazel-archive-keyring.gpg] https://storage.googleapis.com/bazel-apt stable jdk1.8" | sudo tee /etc/apt/sources.list.d/bazel.list
```
```bash
sudo apt update && sudo apt install bazel
```
* Run:
```bash
bazel run //src/queue:queue_arr_bin
```
* Build
```bash
bazel build //src/queue:queue_arr_bin
```