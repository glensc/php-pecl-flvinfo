#!/usr/bin/php
<?php
$file = ($argc > 1 ? $argv[1] : "fall2005.flv");

if (!extension_loaded('flvinfo')) {
	dl('flvinfo.' . PHP_SHLIB_SUFFIX);
}

$res = get_flv_dimensions($file);
if (!isset($res)) {
	echo "res is not set\n";
}
echo "res=[$res]\n";
print_r($res);
