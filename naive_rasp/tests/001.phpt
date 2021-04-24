--TEST--
Check if naive_rasp is loaded
--SKIPIF--
<?php
if (!extension_loaded('naive_rasp')) {
	echo 'skip';
}
?>
--FILE--
<?php
echo 'The extension "naive_rasp" is available';
?>
--EXPECT--
The extension "naive_rasp" is available
