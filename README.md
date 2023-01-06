## IW4_IWD_Generator
This is a program that simplifies the process of porting models between levels in IW4. This tool eliminates the need for manually extracting IWI files and repacking them into an IWD file. All generated IWD files will be stored in the ```spdata``` folder, while all extracted IWI files can be found in a folder called ```custom_iwd```. The ```custom_iwd``` folder is optional and not required for standard usage, but it can be useful if you wish to modify the IWI files before packaging them into an IWD.

Please note that this program is designed to be used with the IW4 codmod, but it can also be used with IW4x by simply moving the outputted IWD file to the appropriate location.

## Very Early Access
Please be aware that this program is in very early access and has limited error checking at this time. To avoid any issues, please carefully follow the instructions provided.

## How To Use
  1. Use Greyhound to find the model you want, ensuring that the "Use Global Image Folder" option is unchecked in the settings. Click "Export" to export the model to disk.
  2. Open the IW4 IWD Generator and input or drag your MW2 root folder into the program. Hit enter.
  3. Drag the folder of the exported Greyhound model onto the program. Hit Enter.
  4. The IWD file will be automatically generated and placed in the spdata folder.
