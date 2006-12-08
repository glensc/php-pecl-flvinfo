#!/bin/sh
PHP=php.cli
#PHP=php4.cli
FILE=/tmp/Krimiuudised_20061204_jegorovi_mure.flv
$PHP -dextension_dir=modules flvinfo.php $FILE
