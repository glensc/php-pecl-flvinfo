#!/usr/bin/php4.cli
<?php
$file = ($argc > 1 ? $argv[1] : "fall2005.flv");

if (!extension_loaded('flvinfo')) {
	echo "loading extension\n";
	dl('flvinfo.' . PHP_SHLIB_SUFFIX);
}

printf("FLV_CODEC_VP3: %s\n", defined('FLV_CODEC_VP3') ? 'yes' : 'no');
printf("FLV_CODEC_VP5: %s\n", defined('FLV_CODEC_VP5') ? 'yes' : 'no');
printf("FLV_CODEC_VP6: %s\n", defined('FLV_CODEC_VP6') ? 'yes' : 'no');
printf("FLV_CODEC_VP6F: %s\n", defined('FLV_CODEC_VP6F') ? 'yes' : 'no');

$res = get_flv_dimensions($file);
if (!isset($res)) {
	echo "res is not set\n";
}
echo "res=[$res]\n";
print_r($res);
