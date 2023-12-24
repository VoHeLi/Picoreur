# Picoreur
## Purpose:
Picoreur is an OpenXR Virtual Runtime designed to facilitate the play of OpenXR games originally intended for a certain Chinese VR headset on a specific French VR headset in standalone mode.

## Technology Stack:
The project is developed using the Android NDK.

# Overview:
Picoreur compiles into a fake OpenXR runtime, which is then loaded by a slightly modified loader within an OpenXR app. This fake runtime serves the purpose of controlling the flow of OpenXR data, allowing for modifications to controller input and other relevant parameters.

## Key Features
Compatibility: Enables the seamless play of OpenXR games meant for a specific Chinese VR headset on a designated French VR headset in standalone mode.

## Data Flow Control: 
The fake OpenXR runtime provides control over the OpenXR data flow, allowing for customization of controller input and other aspects as needed.

## Installation
To install Picoreur, follow these steps:

Before you begin: Make a backup of your device.

### 1. Reflash a Fresh System Version
- Install Qualcomm USB Driver (found in the QPST Folder) and restart your computer.
- Install QPST and open Qualcomm Flash Image Loader (QFIL).
- Shutdown your headset.
- Press volume up and down simultaneously while plugging your headset into the PC.
- Follow the steps here using files from the lynx-dvt... folder.
- After completion, your device should restart automatically.
### 2. Get Your Magisk Patched boot.img Image
- Finish Lynx Onboarding and enable developer mode.
- Plug in your USB Cable and open a terminal in the Lynx Demo Manager folder.
- Execute the following commands:
- ```./adb devices```
- ```./adb -s [DEVICE_ID] shell svc usb setFunctions mtp```
- Copy boot.img from lynx-dvt... folder.
- Install Magisk using Lynx Virtual Display.
- Using scrcpy-console.bat, select and patch boot.img.
- Copy the patched magisk-patched[...].img to your computer.
- Rename it to boot.img.
### 3. Flashing the Modified boot.img on the Device
- In lynx-dvt... folder, rename boot.img to old_boot.img.
- Copy magisk-patched[...].img to lynx-dvt... folder and rename it to boot.img.
- Follow the steps here to flash the patched version.
### 4. Reinstall Magisk and Enable Superuser
- Finish Lynx Onboarding, enable developer mode, and plug in your USB Cable.
- Open a terminal in the Lynx Demo Manager folder and execute:
- ```./adb -s [DEVICE_ID] install -g ../Magisk-v25.1.apk```
- Open Magisk on your Lynx, click Install, and do a direct install. Reboot your device.
- Return to Magisk, go to the Superuser tab, and ensure [SharedUID] Shell is enabled.
### 5. Install Magisk Modules
- In a new terminal window, execute:
- ```./adb -s [DEVICE_ID] shell svc usb setFunctions mtp```
- Copy MagiskHidePropsConf-v6.1.2.zip and LSPosed-v1.9.2-7024-zygisk-release.zip to the internal storage.
- In Magisk, install the modules from storage using scrcpy.
### 6. Install LsPosed and Core Patch
-In Magisk, enable zygisk and reboot your device.
- Execute the following commands:
```./adb -s 6b33ffe9 install -g ../core-patch-4.2.apk```
```./adb -s [DEVICE_ID] reboot```
- In scrcpy, enable Core patch in LSPposed.
### 7. Patch UltraleapTrackingService
-Copy files from Apktool folder to C://Windows.
Execute:
```./adb -s [DEVICE_ID] shell```
```su```
```cd /system/app/UltraleapTrackingService```
```cp UltraleapTrackingService.apk /storage/self/primary/```
- Copy UltraleapTrackingService.apk to your computer.
- Use apktool to modify the AndroidManifest.xml file.
- Copy the new apk to LynxDemoManagerFolder.
- Execute:
- ```./adb -s [DEVICE_ID] install -g ultrapatched.apk```
- ```./adb -s [DEVICE_ID] reboot```
### 8. Install a certain chinese headset's app and Patch the OpenXR Loader
- Execute:
- ```./adb -s [DEVICE_ID] install -g ../VRChat_2023.4.2-1388-e2c7b65750.apk```
- ```./adb -s [DEVICE_ID] shell svc usb setFunctions mtp```
- Copy PicoreurOpenXRLoader files to Internal shared storage.
- Execute the provided commands to patch the OpenXR Loader.
### 9. Install Picoreur Runtime
- Execute:
- ```./adb -s [DEVICE_ID] install -g ../PicoreurRuntime.apk```
-Open the PICOREUR app once and return to Lynx home.
-Execute:
- ```./adb -s [DEVICE_ID] shell svc usb setFunctions mtp```
- Files named picoreur_runtime.json and PicoreurLynxLoaderPath.txt should have appeared.
### 10. Hiding Navbar
- Execute:
-```./adb -s [DEVICE_ID] shell```
- ```su```
- ```props qemu.hw.mainkeys 1```
- Wait until it ends loading, choose yes, and reboot the device.
### 11. Force-Rotate App
- Connect your device to Wifi.
- Execute:
- ```./adb -s [DEVICE_ID] shell pm uninstall jp.snowlife01.android.rotationcontrol```
- ```./adb -s [DEVICE_ID] install "../Rotation Control_5.0.6_apkcombo.com.apk"```
- ```./adb -s [DEVICE_ID] reboot```
- Open Rotation Control app, allow every permission, disable per app settings, and reboot.
### 12. Launch your certain chinese headset's app
- Connect your device to Wifi.
- Execute:
- ``` ./adb -s [DEVICE_ID] shell```
- ```monkey -p com.vrchat.android -c android.intent.category.LAUNCHER 1```
-The first time, use scrcpy to force landscape mode with rotate control.

### Controls
Imagine you have controllers in your hands. Mimic actions as you would with physical controllers.

Note: You can update PicoreurRuntime.apk without redoing the entire process for controller emulator updates.


## Importing the project
The easiest way to compile the fake runtime is to clone the project and open it in Android Studio. You have to install NDK. (And import lynx libopenxr_loader.so)

## Project structure

### OXR
The OXR runtime is where requests from the loader are received

### MIRAGE
Where requests to real OpenXR are sent

### CONTROLLERS
Where controllers emulation is made, it is still very experimental

### OTHER
Other files include Java class to create an empty service necessary for the loader and a quick setup java script for apps to find the fake runtime. It also includes glm, openxr include files and some utils.

