--TEST--
naive_rasp_test1() Basic test
--SKIPIF--
<?php
if (!extension_loaded('naive_rasp')) {
	echo 'skip';
}
?>
--FILE--
<?php
$ret = naive_rasp_test1();

var_dump($ret);
?>
--EXPECT--
The extension naive_rasp is loaded and working!
NULL
