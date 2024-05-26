> [!note] 
> Данная работа является заключительной в рамках лабораторного практикума по разработке на С++ в НИЯУ МИФИ. Классы, в соответствии с паттерном `MVC`, разделены на 3 категории(model, view, controller). Графическая программа выполнена с использованием фреймворка `SFML`. Для классов логики разработаны тесты(использовался фреймворк `catch2`). Все публичные методы классов задокументированы. 
## Легенда
Команда оперативников "Организации" пытается уничтожить группу аномальных неопознанных существ, расположившихся в комплексе помещений. Помещения состоят из стен, перегородок и стёкол. Каждый оперативник имеет характеристики и набор спряжения. Цель оперативников - уничтожить противников с минимальными потерями.

Команды оперативников и их противников ходят по очереди, при этом любой может ходить и выполнять действия в код своей команды. Каждое действие или шаг отнимает определенное кол-во очков времени у сходившего, которые пополняются каждый раз в начале хода команды. Когда у всех в команде кончились очки времени, ход передаётся другой команде.

## Основные механики
Существа  делятся на диких, разумных и одомашненных фуражиров. 
<u>Дикие существа</u> бросаются на оперативников, могут атаковать только в ближнем бою и не имеют инвентаря.
<u>Разумные</u> также не имеют инвентаря, но могут нести одно оружие, и атаковать с помощью него. Перезарядить его, или исполосовать какой-либо другой предмет они не могут, однако могут выбросить имеющееся оружие и поднять другое. 
<u>Фуражиры </u>имеют инвентарь, но не умеют атаковать, вместо этого они ищут предметы по всему полю, собирают их, и сбрасывают в точках складирования. 

В качестве предметов <u>оперативники</u> могут носить в инвентаре <u>оружие</u>, <u>контейнеры</u> с патронами и <u>аптечки</u>, Оперативники могут атаковать только используя оружие, извлечённое из <u>инвентаря</u> и находящееся в руках, и которое может быть заряжено определенным количеством патронов. В случае разрядки оружие оперативник должен его перезарядить, используя патроны из контейнера соответствующего типа. Каждый предмет имеет свой вес, невозможно носить предметов больше чем позволяет сила носящего,

Фуражиры и разумные знают о местоположении складских точек на карте, и могут использовать это знание для более продуманного взаимодействия. Однако никто из них не знает о местоположении разбросанных предметов, поэтому вынуждены их искать. В случае смерти оперативника, фуражира или разумного существа, предметы из его инвентаря падают на пол.

Каждый оперативник и существо имеет определённый радиус обзора, при попадании в который становится виден против, и по нему становится можно стрелять. Если противник вышел за пределы радиуса обзора, он становится снова невидимым для команды. Линия обзора преграждается стенами или перегородками, но не стеклом. Однако стрелять по противнику за стеклом нельзя. Если выстрелить по стеклу или перегородке, они разрушатся, переставая мешать стрельбе.
