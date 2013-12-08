<!DOCTYPE html>
<html>
<head>
  <title>Lab7</title>
  <link rel="stylesheet" type="text/css" href="style.css">

  <?php
  include 'code/Pharmacy.php';
  $data = new FileDataSource;

  #process requests here
  if (isset($_REQUEST['commentSubmit'])) {
    $email = $_REQUEST['commentEmail'];
    $drug = $_REQUEST['commentDrug'];
    $text = $_REQUEST['commentText'];
    $data->addComment($email, $drug, $text);

  } elseif (isset($_REQUEST['orderSubmit'])) {
    $time = time();
    $drug = $_REQUEST['orderedDrug'];
    $count = $_REQUEST['itemsCount'];
    $data->addOrder(new Order($time, $drug, $count));
  }

  ?>
</head>
<body>

<div class="nav">
  <ul>
    <li class="nav_big">Aптека</li>
    <li class="nav_li"><a href="#lec">Лекарства</a></li>
    <li class="nav_li"><a href="#deliv">Поставки</a></li>
    <li class="nav_li"><a href="#purch">Покупки</a></li>
  </ul>
</div>

<div class="content">

  <h2>Лекарства</h2>
  <span><a name="lec"></a></span>
  <table class="t_table">
    <tr class="t_header">
      <th>Наименование</th>
      <th>Производитель</th>
      <th>Форма выпуска</th>
      <th>Цена</th>
    </tr>
    <?php foreach ($data->getDrugs() as $drug) {
      echo '<tr>';
      echo "<td>" . $drug->name . "</td>";
      echo "<td>" . $drug->producer . "</td>";
      echo "<td>" . $drug->formFactor . "</td>";
      echo "<td>" . $drug->price . "</td>";
      echo '</tr>';
    }
    ?>
  </table>
  <br>

  <div id="comment">
    <?php
    $comment = $data->getRandomComment();
    if (!empty($comment)) {
      echo "<h4>Случайный отзыв:</h4>";
      echo "<p>$comment</p>";
    } else {
      echo "<p>No comments</p>";
    }
    ?>

    <h3>Оставьте свой комментарий</h3>

    <form method="post" action="<?php htmlspecialchars($_SERVER['PHP_SELF']); ?>">
      <div class="inline">
        <span>Ваша почта:</span>
        <br>
        <input type="text" name="commentEmail">
        <br>
        <span>Лекарство:</span>
        <br>
        <select name="commentDrug">
          <option value="none" selected>Выберите лекарство</option>
          <?php
          foreach ($data->getDrugs() as $drug) {
            echo "<option value='$drug->name'>$drug->name</option>";
          }
          ?>
        </select>
      </div>
      <div>
        <span>Комментарий:</span>
        <br>
        <textarea name="commentText"></textarea>
        <br>
        <input type="submit" value="Отправить отзыв" name="commentSubmit">
      </div>
    </form>
  </div>

  <h2>Поставки</h2>
  <span><a name="deliv"></a></span>
  <table class="t_table">
    <tr class="t_header">
      <th>Дата</th>
      <th>Наименования</th>
    </tr>
    <tr>
      <td>
        <time>22-11-13</time>
      </td>
      <td>
        <ol>
          <li>
            ТЕРАФЛЕКС
          </li>
          <li>
            АКТОВЕГИН
          </li>
        </ol>
      </td>
    </tr>
    <tr>
      <td>
        <time>01-12-13</time>
      </td>
      <td>
        <ol>
          <li>
            ТОНЗИЛГОН Н
          </li>
          <li>
            АКТОВЕГИН
          </li>
          <li>
            ТЕРАФЛЕКС
          </li>
        </ol>
      </td>
    </tr>
  </table>
  <h2>Покупки</h2>
  <span><a name="purch"></a></span>
  <table class="t_table">
    <tr class="t_header">
      <th>
        Время
      </th>
      <th>
        Наименование
      </th>
      <th>
        Количество
      </th>
      <th>
        Сумма
      </th>
    </tr>


    <?php
    $orders = $data->getOrders();
    foreach ($orders as $order) {
      echo "<tr>";
      echo "<td>" . date("d/m/y h:i:s", $order->time) . "</td>";
      echo "<td>$order->drugs</td>";
      echo "<td>$order->count</td>";

      #calculate sum
      $allDrugs = $data->getDrugs();
      $sum = 0;
      foreach ($allDrugs as $drug) {
        if ($drug->name == $order->drugs) {
          $sum += $drug->price * $order->count;
          break;
        }
      }
      echo "<td>$sum</td>";
      echo "</tr>";
    }
    ?>
  </table>

  <h3>Сделайте заказ</h3>
  <form method="post" action="<?php htmlspecialchars($_SERVER['PHP_SELF']); ?>">
    <div class="inline">
      <span>Лекарство:</span>
      <br>
      <select name="orderedDrug">
        <option value="none" selected>Выберите лекарство</option>
        <?php
        foreach ($data->getDrugs() as $drug) {
          echo "<option value='$drug->name'>$drug->name</option>";
        }
        ?>
      </select>
    </div>
    <div>
      <span>Количество:</span>
      <br>
      <input type="text" name="itemsCount" value="1">
      <br>
      <input type="submit" value="Заказать" name="orderSubmit">
    </div>
  </form>
</div>
</body>
</html>