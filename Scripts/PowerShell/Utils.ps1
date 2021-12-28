# This script contain useful PowerShell functions for XMiLib
#
# Author: Xavier Michelon
#
# Copyright (c) Xavier Michelon. All rights reserved.  
# Licensed under the MIT License. See LICENSE file in the project root for full license information.  


$vsPath = "C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\IDE\devenv.com"


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
function compileVisualStudioSolution([String]$solutionPath, [String]$configuration = "Release|x64")
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
   $qtDir = $env:QT6DIR
   if ([String]::IsNullOrEmpty($qtDir))
   {
       Write-Error "The QTDIR environment variable is not define (should be something like C:\Qt\5.10\msvc217)"
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
   $qtDlls = "Qt6Core.dll", "Qt6Gui.dll", "Qt6Network.dll", "Qt6Widgets.dll"
   foreach ($dll in $qtDlls) { Copy-Item -Path (absolutePath $qtDir  "bin\$dll") -Destination $dstPath }
   $folders = "imageformats", "platforms", "styles", "tls"
   foreach ($folder in $folders) { New-Item -ItemType Directory -Force -Path (absolutePath $dstPath $folder) | Out-Null }
   $qtPlugins = "imageformats\qico.dll", "platforms\qwindows.dll", "styles\qwindowsvistastyle.dll", 
      "tls\qcertonlybackend.dll", "tls\qopensslbackend.dll", "tls\qschannelbackend.dll"
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
