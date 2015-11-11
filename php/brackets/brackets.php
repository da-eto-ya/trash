<?php
assert_options(ASSERT_BAIL, 1);

/**
 * Проверяет, что срока представляет собой сбалансированную скобочную последовательность.
 *
 * Алгоритм имеет линейную сложность по времени O(strlen($str)), поскольку мы проходим
 * последовательно по каждому символу строки и для него делаем максимум одно действие со стеком.
 *
 * Алгоритм имеет линейную сложность по памяти O(strlen($str)), поскольку в худшем случае мы
 * можем добавить в стек ровно столько символов, сколько есть в строке (если это открывающие скобки).
 *
 * @param string $str
 * @return bool
 */
function is_balanced($str)
{
    static $openBrackets = ['(' => ')', '[' => ']', '{' => '}',];
    static $closeBrackets = [')' => '(', ']' => '[', '}' => '{',];

    // в стеке будем хранить последовательность открывающих скобок,
    // для каждой встреченной закрывающей будем проверять, что ей
    // соответствует открывающая на вершине стека
    $stack = [];

    for ($i = 0, $n = strlen($str); $i < $n; ++$i) {
        $br = $str[$i];

        if (isset($openBrackets[$br])) {
            // открывающие скобки кладём в стек
            array_push($stack, $br);
        } else {
            // встретили символ, который не открывающая и не закрывающая скобка
            if (!isset($closeBrackets[$br])) {
                return false;
            }

            // для закрывающих скобок проверяем вершину стека
            if (array_pop($stack) !== $closeBrackets[$br]) {
                return false;
            }
        }
    }

    // если стек не пуст, значит, в нём остались открывающие скобки
    return empty($stack);
}


assert(true == is_balanced(''));
assert(false == is_balanced('a'));
assert(false == is_balanced(']]'));
assert(true == is_balanced('[]'));
assert(false == is_balanced('[]['));
assert(true == is_balanced('[({}{}{}[]())]'));

assert(true == is_balanced('()[]{}(([])){[()][]}'));
assert(false == is_balanced('())[]{}'));
assert(false == is_balanced('[(])'));

echo "Ok\n";

