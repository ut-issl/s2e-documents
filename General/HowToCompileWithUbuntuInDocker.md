# How to compile with Ubuntu in Docker 

## 1.  Overview
- [Docker](https://www.docker.com/) is useful for easy setup of the compile environment for S2E.
- *Both Windows and Mac* users can use same environment and get same result by using the docker container.
- We selected [Ubuntu](https://ubuntu.com/) as an OS in the docker and [GCC/G++](https://gcc.gnu.org/) as an compiler for S2E.
  - **Note**: Currently, we use 32bit compiler for S2E since flight S/Ws are usually executed on 32 bit micro-computers. 
- We recommend to use [Visual Studio Code](https://code.visualstudio.com/) as an editor for the environment.
- This document explains a sequence of setup the docker environment for S2E. 

## 2.  Install Required Application
### 2.1. Docker
- Go [install web page of Docker](https://docs.docker.com/get-docker/)
- Install `Docker for Windows` or `Docker for Mac` to suit with your platform.

### 2.2. Visual Studio Code (VS Code)
- Go [install web page of VS Code](https://code.visualstudio.com/)
- Install `Visual Studio Code` to suit with your platform.
- Install following extensions
  - Remote-SSH
  - CMake
  - CMake Tools
  - C/C++
- Following extensions are also useful
  - Markdown+Math  
    please change the delimiter setup to use same math format with `Gitlab`. 
  - Code Spell Checker

### 2.3. **For Mac users**
- Install `coreutils` to use `realpath` command in `setup_docker.sh`
- Use the bottom command when you have `Homebrew`  
  `brew install coreutils`

## 3. Sequence of environment setting
### 3.1. Working directory setting
- Create `work` directory as a working directory.
- Clone [S2E_CORE_OSS](https://gitlab.com/ut_issl/s2e/s2e_core_oss) in the `work` directory.
- Add the `work` directory in the `file sharing` directory of Docker.

### 3.2. Make Docker image and container
- Launch `git bush` (for windows users) or `terminal` (for Mac users)
- Move `/s2e_core_oss/scripts/Docker_Ubuntu` directory
- Edit `Dockerfile` or `setup_docker.sh` if you need.  
  when you want to change directory name, user name of the container, and so on.
- Execute `./setup_docker.sh build` to make images
- Check created image (`issl` (and `ubuntu`))  
  command: `docker images`
- Execute `./setup_docker.sh run_core` to make a container
- Check created container (`issl:latest`)  
  command: `docker ps -a`
- Check dashboard of Docker 
<div align="center">
  <img src="./figs/Docker_container.png" alt="DockerContainer" style="zoom:30%;" />
</div>

### 3.3. SSH connect with VS Code
- Launch `VS Code` and open new window
- Click `Remote Explorer` icon in the left side  
  note: the icon looks a monitor 
- Click `gear` icon of `SSH TARGETS` and select config file you want to edit  
  Default: `C:\Users\UserName\ssh\config` or `User/UserName/ssh/config`
- Edit the config file as follows
``` 
Host issl-1
  HostName localhost
  User s2e
  Port 2222
```
- Save the config file and check a new SSH target `issl-1` is made in the explorer
- Click `Connect to Host in New Window` icon on right side of `issl-1`
- Enter the password `s2e` when required
- See left bottom icon `SSH:issl-1` to confirm the connection
- Open `work` directory in the container by using `Open folder`
<div align="center">
  <img src="./figs/VSC_SSH_connect.png" alt="VSC_SSH_connect" style="zoom:30%;" />
</div>

### 3.4. Setting of build environment
- S2E has several script files to get external libraries.
- For this ubuntu/docker platform, users should use script files in `scripts/Common` directory and `scripts/Docker_Ubuntu` directory.
- Users can execute the most of the script files with `git bush` or `terminal` in the outside of container, but users should execute `scripts/Common/download_nrlmsise00_src_and_table.sh` inside the container to use same compiler.
- Click `Terminal > New terminal` in the menu bar of VS Code
- Select `bash` terminal at the bottom window
- execute `./s2e_core_oss/scripts/Common/download_nrlmsise00_src_and_table.sh`
- See `ExtLibraries` to confirm the NRLMSISE library is generated.

**Note** : This sequence will be integrated within the docker container creation for more easy setting
 

### 3.5. Build S2E
- Install following extensions in the `issl-1 SSH connection`  
  the extensions were already installed in local VS code, but you also need install them in the `SSH connection`
  - C/C++
  - CMake
  - CMake Tools  
**Note** : you need to reload VS Code after install new extensions
- Edit setting of `CMake Tools` in `issl-1`  
  `Cmake Build Directory: ${workspaceFolder}/s2e_core_oss/build/Debug`
- After `CMake` and `CMake Tools` are installed, VS Code require you to configure build environment with `CMakeList.txt`. Please select `yes`. But there is no `CMakeList.txt` file in the `work` directory, and VS Code require you to locate `CMakeList.txt`, so please select the `CMakeList.txt` file in `s2e_core_oss` directory.
  - This setting is written in `.vscode/settings.json`
  - You can directly edit the `settings.json` as follows
  ```json
  "cmake.sourceDirectory": "${workspaceFolder}/s2e_core_oss",
  "cmake.buildDirectory": "${workspaceFolder}/s2e_core_oss/build/Debug",
  ```
- Select `GCC 9.3.0` as a kit (compiler) 
- Select `CMake [Debug]` and check the configuration is successfully done.
- Build S2E
  - If you want clean up build, please use `CMake: Clean` command
- Move `build/Debug` directory with `Terminal` in VS Code
- Execute `run` command or click `run` icon in bottom
- Check `data/log` directory to confirm log file output

## 4. Debug with VS Code
- Select `Run > Start Debugging` in the menu bar.
- Select `C++(GDB/LLDB)` debugger  
  `.vscode/launch.json` will be created.
- Edit as follows
```json
"program": "${workspaceFolder}/s2e_core_oss/build/Debug/S2E",

"cwd": "${workspaceFolder}/s2e_core_oss/build/Debug",
```
- Select `Run > Start Debugging` again
- Check `data/log` directory to confirm log file output
- You can use break point in the VS Code editor