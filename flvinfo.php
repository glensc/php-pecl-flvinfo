<?php
$br = (php_sapi_name() == 'cli') ? '' : '<br>';

if(!extension_loaded('flvinfo')) {
	dl('flvinfo.' . PHP_SHLIB_SUFFIX);
}
$module = 'flvinfo';
$functions = get_extension_funcs($module);
echo "Functions available in the test extension:$br\n";
foreach($functions as $func) {
    echo $func."$br\n";
}
echo "$br\n";

$res = get_flv_dimensions("fall2005.flv");
if (!isset($res)) {
	echo "res is not set\n";
}
echo "res=[$res]\n";
print_r($res);

?>
