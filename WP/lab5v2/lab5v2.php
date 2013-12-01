<?php
//2. Дан массив букв. Найти частоту появления
// каждой буквы, вывести в процентах.
$input = "The quick brown fox jumps over the lazy dog. And winner is ZZZZZZZZZZZZZZ!";
$stat = array();
$caseingore = true;

echo "Input is: $input";

$totalChars = strlen($input);
for ($i = 0; $i < $totalChars; $i++) {
    $key = $input[$i];

    if ($caseingore)
        $key = strtolower($key);

    if (array_key_exists($key, $stat)) {
        $stat[$key] = $stat[$key] + 1;
    } else {
        $stat[$key] = 1;
    }
}

arsort($stat);
echo "<ol>";
foreach($stat as $k => $v) {
    $perecentage = ($v*100)/$totalChars;
    echo "<li style='font-size: 80%;'>'$k' => $perecentage </li>";
}
echo "</ol>"

?>