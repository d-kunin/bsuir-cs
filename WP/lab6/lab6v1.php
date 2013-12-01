<?php
// В файле 1.txt записан массив слов
// (1 слово - 1 строчка). Создать файл
// 2.txt в котором записаны 12 предложений,
// составленный из слов в файле 1.txt. Каждое
// предложение с новой строки, начинается
// с Заглавной буквы и кончается точкой.

function mb_ucfirst($str, $encoding = 'UTF-8')
{
  $str = mb_ereg_replace('^[\ ]+', '', $str);
  $str = mb_strtoupper(mb_substr($str, 0, 1, $encoding), $encoding) .
    mb_substr($str, 1, mb_strlen($str), $encoding);
  return $str;
}

function write_result($sentences)
{
  $file = fopen("2.txt", "w");
  foreach ($sentences as $s)
    fwrite($file, $s . "\n");
  fclose($file);
}

$words = explode("\n", file_get_contents("1.txt"));
$sentences = array();

echo "source words count: " . count($words);
echo "<ol>";

for ($i = 0; $i < 12; $i++) {
  $w_indexes = array_rand($words, rand(3, 8));
  $sent = "";
  foreach ($w_indexes as $index)
    $sent .= $words[$index] . " ";

  $sent = trim($sent);
  $sent = mb_ucfirst($sent);
  $sent .= ".";

  $sentences[$i] = $sent;
  echo "<li>$sent</li>";
}
echo "</ol>";
write_result($sentences);
?>