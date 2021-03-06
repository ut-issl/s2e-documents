# How to compile with Ubuntu in Docker 

## 1.  Overview
- [Docker](https://www.docker.com/) is useful for the easy setup of the compile environment for S2E.
- *Both Windows and Mac* users can use the same environment and get the same result by using the docker container.
- We selected [Ubuntu](https://ubuntu.com/) as an OS in the docker image and [GCC/G++](https://gcc.gnu.org/) as a compiler for S2E.  
  **Note**: We currently use a 32bit compiler for S2E since flight S/Ws are usually executed on a 32bit microcomputers. 
- We recommend using [Visual Studio Code](https://code.visualstudio.com/) as an editor for the environment.
- This document explains a setup sequence of the docker environment for S2E.
- Note: For a detailed explanation of Docker and VSCode's Extensions, please see the latest and official information.

## 2.  Install Required Application
### 2.1. Docker
- Go to the [install web page of Docker](https://docs.docker.com/get-docker/).
- Install `Docker for Windows` or `Docker for Mac` to suit your platform.

### 2.2. Visual Studio Code (VS Code)
- Go [install web page of VS Code](https://code.visualstudio.com/).
- Install `Visual Studio Code` to suit your platform.
- Install following extensions
  - Remote-SSH
  - CMake
  - CMake Tools
  - C/C++
- Following extensions are also useful
  - Code Spell Checker

### 2.3. **For Mac users**
- Install the `coreutils` to use the `realpath` command in `setup_docker.sh`
  - Use the `brew install coreutils` command when you have `Homebrew`  

## 3. A Sequence of environment setting
### 3.1. Working directory setting
- Create a `work` directory as a working directory.
- Clone [s2e-core](https://github.com/ut-issl/s2e-core) in the `work` directory.
- Add the `work` directory in the `file sharing` directory of Docker.  
  - **Note**: This setting does not exist in the latest Docker and WSL2 environments in Windows, so it is not necessary.

### 3.2. Make Docker image and container
- Launch `git bash` (for windows users) or `terminal` (for Mac users)
- Move `/s2e-core/scripts/Docker_Ubuntu` directory
- Edit `Dockerfile` or `setup_docker.sh` when you want to change the directory name, the user name of the container, and other settings.
- Execute `./setup_docker.sh build` to make images
- Check created images (`issl` (and `ubuntu`))
  - command: `docker images`
- Execute `./setup_docker.sh run_core` to make the container
- Check created container (`issl:latest`)
  - command: `docker ps -a`
- Check the dashboard of Docker as follows.
  <div align="center">
    <img src="./figs/Docker_container.png" alt="DockerContainer" style="zoom:30%;" />
  </div>

### 3.3. SSH connects with VS Code
- Launch `VS Code` and open a new window.
- Click the `Remote Explorer` icon on the left side.
  - Note: the icon looks like a monitor
- Click the `gear` icon of `SSH TARGETS` and select the config file you want to edit  
  - Default: `C:\Users\UserName\ssh\config` or `User/UserName/ssh/config`
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
- Open the `work` directory in the container by using `Open folder`
  <div align="center">
    <img src="./figs/VSC_SSH_connect.png" alt="VSC_SSH_connect" style="zoom:30%;" />
  </div>

### 3.4. Download External Libraries
**Note** : This sequence was integrated within the docker build process, so this is currently unnecessary.

- S2E has several script files to get external libraries.
- For this ubuntu/docker platform, users should use script files in `scripts/Common` directory and `scripts/Docker_Ubuntu` directory.
- Users can execute most of the script files with `git bash` or `terminal` in the outside of the container, but users should execute `scripts/Common/download_nrlmsise00_src_and_table.sh` inside the container to use the same compiler.
- Click `Terminal > New terminal` in the menu bar of VS Code.
- Select `bash` terminal at the bottom window.
- Execute `./s2e-core/scripts/Common/download_nrlmsise00_src_and_table.sh`.
- See `ExtLibraries` to confirm the NRLMSISE library is generated.
 

### 3.5. Build S2E
- Install the following extensions in the `issl-1 SSH connection`  
  Even if the extensions were already installed in local VS code, you also need to install them in the `SSH connection`.
  - C/C++
  - CMake
  - CMake Tools  
  **Note** : You need to reload VS Code after installing new extensions
- Edit setting of `CMake Tools` in `issl-1`
  ```
  Cmake Build Directory: ${workspaceFolder}/s2e-core/build/Debug
  ```
- After `CMake` and `CMake Tools` are installed, VS Code requires you to configure the building environment with `CMakeList.txt`. Please select `yes`. However, there is no `CMakeList.txt` file in the `work` directory, and VS Code requires you to locate `CMakeList.txt`, so please select the `CMakeList.txt` file in `s2e-core` directory.
  - This setting is written in `.vscode/settings.json`
  - You can directly edit the `settings.json` as follows
    ```json
    {
      "cmake.sourceDirectory": "${workspaceFolder}/s2e-core",
      "cmake.buildDirectory": "${workspaceFolder}/s2e-core/build/Debug"
    }
    ```
- Select `GCC 11.2.0` as a kit (compiler)
  - Note: Users can also choose other GCC versions. 
- Select `CMake [Debug]` and check the configuration is successfully done.
- Build S2E
  - If you want to clean up, please use `CMake: Clean` command.
- Move to `build/Debug` directory with `Terminal` in VS Code.
- Execute `./S2E` or click the `run` icon at the bottom.
- Check the `data/log` directory to confirm log file output.

## 4. Debug with VS Code
- Select `Run > Start Debugging` in the menu bar.
- Select `C++(GDB/LLDB)` debugger  
  - If `C++(GDB/LLDB)` is not shown, please open a CPP file and select `Run > Start Debugging` again.
  - `.vscode/launch.json` will be created.
- Edit as follows.
  ```json
  "program": "${workspaceFolder}/s2e-core/build/Debug/S2E",
  "cwd": "${workspaceFolder}/s2e-core/build/Debug",
  ```
- Select `Run > Start Debugging` again.
- Check the `data/log` directory to confirm log file output.
- You can use breakpoints in the VS Code editor.
