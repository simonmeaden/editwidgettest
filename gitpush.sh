#!/bin/bash 
if [ $# -ne 1 ]; then
    echo "You need to provide a commit message"
    exit
fi

files=( 
	"libs/Docker"
	"libs/Help"
	"libs/LabelledWidgets"
	"libs/Language"
	"libs/QHtml"
	"libs/QLNPlainText"
	"libs/QMarkdown"
	"libs/QXml"
	"libs/QYaml"
	"libs/Utilities"
	"libs/Widgets" 
)

git submodule foreach git add -A .
#git submodule foreach git commit -am "$1"

for s in ${files}
do
  cd ${s}
  git add .
  git commit -m "$1"
  git push
  cd "../.."
done

git add -A .
git commit -am "$1"
