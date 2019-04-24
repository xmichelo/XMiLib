# This script contain useful PowerShell functions for XMiLib
#
# Author: Xavier Michelon
#
# Copyright (c) Xavier Michelon. All rights reserved.  
# Licensed under the MIT License. See LICENSE file in the project root for full license information.  


$vsPath = "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\IDE\devenv.com"


#***********************************************************************************************************************
# Returns the absolute path obtain by merging path1 and path2
#***********************************************************************************************************************
function absolutePath([String]$path)
{
   [System.IO.Path]::GetFullPath($path)
}


#***********************************************************************************************************************
# Returns the absolute path obtain by merging path1 and path2
#***********************************************************************************************************************
function absolutePath([String]$path1, [String]$path2)
{
   [System.IO.Path]::GetFullPath([System.IO.Path]::Combine($path1, $path2))
}


#***********************************************************************************************************************
# Compiles a solution using Visual Studio
#***********************************************************************************************************************
function compileVisualStudioSolution([String]$solutionPath, [String]$configuration = "Release|x86")
{
   $buildLog = Invoke-Expression '& "$vsPath" "$solutionPath" /rebuild "$configuration"' | Out-Null
   if (0 -ne $LASTEXITCODE)
   {
      $buildLog # dump the build log
      Write-Error "Compilation of the application failed."
   }
}


#***********************************************************************************************************************
# Check for the existence of the Qt installation folder and returns it
#***********************************************************************************************************************
function checkQtInstallation()
{
   $qtDir = $env:QTDIR_XMILIB
   if ([String]::IsNullOrEmpty($qtDir))
   {
       Write-Error "The QTDIR_XMILIB environment variable is not define (should be something like C:\Qt\5.10\msvc217)"
   }
   if(!(Test-Path $qtDir -PathType Container))
   {
      Write-Error "The Qt installation folder '$qtDir' does not exist."
   }
   $qtDir
}

#***********************************************************************************************************************
# Copy the Qt DLLS required by Beeftext to the destination folder
#***********************************************************************************************************************
function copyQtDlls([String]$dstPath)
{
   $qtDir = checkQtInstallation
   $qtDlls = "Qt5Core.dll", "Qt5Gui.dll", "Qt5Multimedia.dll", "Qt5Network.dll", "Qt5Widgets.dll"
   foreach ($dll in $qtDlls) { Copy-Item -Path (absolutePath $qtDir  "bin\$dll") -Destination $dstPath }
   $folders = "audio", "imageformats", "platforms", "styles"
   foreach ($folder in $folders) { New-Item -ItemType Directory -Force -Path (absolutePath $dstPath $folder) | Out-Null }
   $qtPlugins = "audio\qtaudio_windows.dll", "imageformats\qico.dll", "platforms\qwindows.dll", "styles\qwindowsvistastyle.dll"
   foreach ($dll in $qtPlugins) { Copy-Item -Path (absolutePath $qtDir "plugins\$dll") -Destination (absolutePath $dstPath $dll) }    
}


#***********************************************************************************************************************
# Generate the binary .qm translation file from a source .ts file 
#***********************************************************************************************************************
function compileTranslationFiles([String]$tsFilePath, [String]$dstFolder)
{
   $qtDir = checkQtInstallation
   $tsFileName = (Split-Path -Path $tsFilePath -Leaf)
   $qmFilePath = absolutePath $dstFolder ([System.IO.Path]::GetFileNameWithoutExtension($tsFileName) + ".qm")
   $lreleaseBinPath = absolutePath $qtDir "bin\lrelease.exe";
   if(![System.IO.File]::Exists($lreleaseBinPath)){
      Write-Error "Could note locate lrelease.exe (not found at '$lreleaseBinPath')"
   }
   Write-Output "compiling TS file $tsFileName to $qmFilePath";
   Invoke-Expression '& "$lreleaseBinPath" "$tsFilePath" -qm "$qmFilePath"' | Out-Null
   if (0 -ne $LASTEXITCODE)
   {
      Write-Error "Compilation of the translation file failed."
   }
}
