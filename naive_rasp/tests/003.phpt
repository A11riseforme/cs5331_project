--TEST--
naive_rasp_test2() Basic test
--SKIPIF--
<?php
if (!extension_loaded('naive_rasp')) {
	echo 'skip';
}
?>
--FILE--
<?php
var_dump(naive_rasp_test2());
var_dump(naive_rasp_test2('PHP'));
?>
--EXPECT--
string(11) "Hello World"
string(9) "Hello PHP"
