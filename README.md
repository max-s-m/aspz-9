# Завдання 1

## Умова:

Напишіть програму, яка читає файл /etc/passwd за допомогою команди getent passwd, щоб дізнатись, які облікові записи визначені на вашому комп’ютері.
Програма повинна визначити, чи є серед них звичайні користувачі (ідентифікатори UID повинні бути більші за 500 або 1000, залежно від вашого дистрибутива), окрім вас.

## [Програмний код](1.c)

## Опис:

Створена програма визначає та виводить на екран всі облікові записи на пристрої, окрім поточного, які мають uid
більше за те, що було передане у якость аргумента (для тестування різних випадків). Це реалізовано
шляхом відкриття пайпу (створює паралельний процес, запускає на ньому передану команду, та повертає її вивід) та
запуском у ній команди getent passwd. Мій пристрій не має інших облікових записів, тобто звичайних користувачів
(UID > 1000), окрім max (основний, на якому запущено команду), тому виводом програми приаргументі 1000  є 'nobody'.
Якщо ж у якості аргумента передати 0 (починаючи з рут юзера), то можна побачити значно більше "не звичайних" користувачів.
Для тестування запущено програму з аргументами 0 та 1000 по черзі.

## Результат виконання:

```
max@aspz:~/c/9 $ gcc -Wall 1.c -o 1
max@aspz:~/c/9 $ ./1 0
root
toor
daemon
operator
bin
tty
kmem
games
news
man
sshd
smmsp
mailnull
bind
unbound
proxy
_pflogd
_dhcp
uucp
pop
auditdistd
www
ntpd
_ypldap
hast
tests
nobody
messagebus
polkitd
avahi
colord
cups
pulse
cyrus
mysql
saned
webcamd
sddm
_sndio
max@aspz:~/c/9 $ ./1 1000
nobody
max@aspz:~/c/9 $
```

# Завдання 2

## Умова:

Напишіть програму, яка виконує команду cat /etc/shadow від імені адміністратора, хоча запускається від звичайного користувача.
(Ваша програма повинна робити необхідне, виходячи з того, що конфігурація системи дозволяє отримувати адміністративний доступ за допомогою відповідної команди.)

## [Програмний код](2.c)

## Опис:

Створена програма, що відкриває /etc/master.passwd, а не /etc/shadow, оскільки з шедоу з'явилася пробдема.
shadow відсутня на моєму девайсі, що скоріш за все через те, що зашифровані паролі на FreeBSD зберігаються
у master.passwd, яка як і shadow, потребує рут прав (можна побачити на початку результатів роботи.), тому
обрано замінити shadow на master.passwd. Сама програма проста і отримує доступ та виводить дані з цього файлу,
запускаючи команду cat /etc/master.passwd з аргументом sudo через system(), що дозволяє при запуску з користувача
max, без судо у консолі, отримати доступ до цього файлу. Для тестування спочатку проведено перегляд файлу вручну,
а далі (може важко видно через довжину виводу) запущено програму.

## Результат виконання:

```
max@aspz:~/c/9 $ sudo cat etc/shadow
cat: etc/shadow: No such file or directory
max@aspz:~/c/9 $ cat /etc/master.passwd
cat: /etc/master.passwd: Permission denied
max@aspz:~/c/9 $ sudo cat /etc/master.passwd
root:$6$mZqTSffaV4nT//yQ$5kBs9xxUsr7BmycFHDP8sb8COgZFM51bPXkYx2gvuTY5frYhiL04VEoHk9xdZs2Cuug4CORohz1b.2QoyK46h1:0:0::0:0:Charlie &:/root:/bin/sh
toor:*:0:0::0:0:Bourne-again Superuser:/root:
daemon:*:1:1::0:0:Owner of many system processes:/root:/usr/sbin/nologin
operator:*:2:5::0:0:System &:/:/usr/sbin/nologin
bin:*:3:7::0:0:Binaries Commands and Source:/:/usr/sbin/nologin
tty:*:4:65533::0:0:Tty Sandbox:/:/usr/sbin/nologin
kmem:*:5:65533::0:0:KMem Sandbox:/:/usr/sbin/nologin
games:*:7:13::0:0:Games pseudo-user:/:/usr/sbin/nologin
news:*:8:8::0:0:News Subsystem:/:/usr/sbin/nologin
man:*:9:9::0:0:Mister Man Pages:/usr/share/man:/usr/sbin/nologin
sshd:*:22:22::0:0:Secure Shell Daemon:/var/empty:/usr/sbin/nologin
smmsp:*:25:25::0:0:Sendmail Submission User:/var/spool/clientmqueue:/usr/sbin/nologin
mailnull:*:26:26::0:0:Sendmail Default User:/var/spool/mqueue:/usr/sbin/nologin
bind:*:53:53::0:0:Bind Sandbox:/:/usr/sbin/nologin
unbound:*:59:59::0:0:Unbound DNS Resolver:/var/unbound:/usr/sbin/nologin
proxy:*:62:62::0:0:Packet Filter pseudo-user:/nonexistent:/usr/sbin/nologin
_pflogd:*:64:64::0:0:pflogd privsep user:/var/empty:/usr/sbin/nologin
_dhcp:*:65:65::0:0:dhcp programs:/var/empty:/usr/sbin/nologin
uucp:*:66:66::0:0:UUCP pseudo-user:/var/spool/uucppublic:/usr/local/libexec/uucp/uucico
pop:*:68:6::0:0:Post Office Owner:/nonexistent:/usr/sbin/nologin
auditdistd:*:78:77::0:0:Auditdistd unprivileged user:/var/empty:/usr/sbin/nologin
www:*:80:80::0:0:World Wide Web Owner:/nonexistent:/usr/sbin/nologin
ntpd:*:123:123::0:0:NTP Daemon:/var/db/ntp:/usr/sbin/nologin
_ypldap:*:160:160::0:0:YP LDAP unprivileged user:/var/empty:/usr/sbin/nologin
hast:*:845:845::0:0:HAST unprivileged user:/var/empty:/usr/sbin/nologin
tests:*:977:977::0:0:Unprivileged user for tests:/nonexistent:/usr/sbin/nologin
nobody:*:65534:65534::0:0:Unprivileged user:/nonexistent:/usr/sbin/nologin
max:$6$3bdR3fzrhYeDbyPU$/s2oeUqJeQJEEf7/OyXbvlnVwSUEsBfsHWrnTGyVXhHgkDWbOjNmvueC1d/brsJaY/6TtFdxbbzN9NPs1a6XU0:1001:1001::0:0:Maksym:/home/max:/bin/sh
messagebus:*:556:556::0:0:D-BUS Daemon User:/nonexistent:/usr/sbin/nologin
polkitd:*:565:565::0:0:Polkit Daemon User:/var/empty:/usr/sbin/nologin
avahi:*:558:558::0:0:Avahi Daemon User:/nonexistent:/usr/sbin/nologin
colord:*:970:970::0:0:colord color management daemon:/nonexistent:/usr/sbin/nologin
cups:*:193:193::0:0:Cups Owner:/nonexistent:/usr/sbin/nologin
pulse:*:563:563::0:0:PulseAudio System User:/nonexistent:/usr/sbin/nologin
cyrus:*:60:60::0:0:the cyrus mail server:/nonexistent:/usr/sbin/nologin
mysql:*:88:88::0:0:MySQL Daemon:/var/db/mysql:/usr/sbin/nologin
saned:*:194:194::0:0:SANE Scanner Daemon:/nonexistent:/bin/sh
webcamd:*:145:145::0:0:Webcamd user:/var/empty:/usr/sbin/nologin
sddm:*:219:219::0:0:SDDM Display Manager user:/var/lib/sddm:/usr/sbin/nologin
_sndio:*:702:702::0:0:sndio privsep:/var/empty:/usr/sbin/nologin
max@aspz:~/c/9 $ gcc -Wall 2.c -o 2
max@aspz:~/c/9 $ ./2
root:$6$mZqTSffaV4nT//yQ$5kBs9xxUsr7BmycFHDP8sb8COgZFM51bPXkYx2gvuTY5frYhiL04VEoHk9xdZs2Cuug4CORohz1b.2QoyK46h1:0:0::0:0:Charlie &:/root:/bin/sh
toor:*:0:0::0:0:Bourne-again Superuser:/root:
daemon:*:1:1::0:0:Owner of many system processes:/root:/usr/sbin/nologin
operator:*:2:5::0:0:System &:/:/usr/sbin/nologin
bin:*:3:7::0:0:Binaries Commands and Source:/:/usr/sbin/nologin
tty:*:4:65533::0:0:Tty Sandbox:/:/usr/sbin/nologin
kmem:*:5:65533::0:0:KMem Sandbox:/:/usr/sbin/nologin
games:*:7:13::0:0:Games pseudo-user:/:/usr/sbin/nologin
news:*:8:8::0:0:News Subsystem:/:/usr/sbin/nologin
man:*:9:9::0:0:Mister Man Pages:/usr/share/man:/usr/sbin/nologin
sshd:*:22:22::0:0:Secure Shell Daemon:/var/empty:/usr/sbin/nologin
smmsp:*:25:25::0:0:Sendmail Submission User:/var/spool/clientmqueue:/usr/sbin/nologin
mailnull:*:26:26::0:0:Sendmail Default User:/var/spool/mqueue:/usr/sbin/nologin
bind:*:53:53::0:0:Bind Sandbox:/:/usr/sbin/nologin
unbound:*:59:59::0:0:Unbound DNS Resolver:/var/unbound:/usr/sbin/nologin
proxy:*:62:62::0:0:Packet Filter pseudo-user:/nonexistent:/usr/sbin/nologin
_pflogd:*:64:64::0:0:pflogd privsep user:/var/empty:/usr/sbin/nologin
_dhcp:*:65:65::0:0:dhcp programs:/var/empty:/usr/sbin/nologin
uucp:*:66:66::0:0:UUCP pseudo-user:/var/spool/uucppublic:/usr/local/libexec/uucp/uucico
pop:*:68:6::0:0:Post Office Owner:/nonexistent:/usr/sbin/nologin
auditdistd:*:78:77::0:0:Auditdistd unprivileged user:/var/empty:/usr/sbin/nologin
www:*:80:80::0:0:World Wide Web Owner:/nonexistent:/usr/sbin/nologin
ntpd:*:123:123::0:0:NTP Daemon:/var/db/ntp:/usr/sbin/nologin
_ypldap:*:160:160::0:0:YP LDAP unprivileged user:/var/empty:/usr/sbin/nologin
hast:*:845:845::0:0:HAST unprivileged user:/var/empty:/usr/sbin/nologin
tests:*:977:977::0:0:Unprivileged user for tests:/nonexistent:/usr/sbin/nologin
nobody:*:65534:65534::0:0:Unprivileged user:/nonexistent:/usr/sbin/nologin
max:$6$3bdR3fzrhYeDbyPU$/s2oeUqJeQJEEf7/OyXbvlnVwSUEsBfsHWrnTGyVXhHgkDWbOjNmvueC1d/brsJaY/6TtFdxbbzN9NPs1a6XU0:1001:1001::0:0:Maksym:/home/max:/bin/sh
messagebus:*:556:556::0:0:D-BUS Daemon User:/nonexistent:/usr/sbin/nologin
polkitd:*:565:565::0:0:Polkit Daemon User:/var/empty:/usr/sbin/nologin
avahi:*:558:558::0:0:Avahi Daemon User:/nonexistent:/usr/sbin/nologin
colord:*:970:970::0:0:colord color management daemon:/nonexistent:/usr/sbin/nologin
cups:*:193:193::0:0:Cups Owner:/nonexistent:/usr/sbin/nologin
pulse:*:563:563::0:0:PulseAudio System User:/nonexistent:/usr/sbin/nologin
cyrus:*:60:60::0:0:the cyrus mail server:/nonexistent:/usr/sbin/nologin
mysql:*:88:88::0:0:MySQL Daemon:/var/db/mysql:/usr/sbin/nologin
saned:*:194:194::0:0:SANE Scanner Daemon:/nonexistent:/bin/sh
webcamd:*:145:145::0:0:Webcamd user:/var/empty:/usr/sbin/nologin
sddm:*:219:219::0:0:SDDM Display Manager user:/var/lib/sddm:/usr/sbin/nologin
_sndio:*:702:702::0:0:sndio privsep:/var/empty:/usr/sbin/nologin
max@aspz:~/c/9 $
```

# Завдання 3

## Умова:

Напишіть програму, яка від імені root копіює файл, який вона перед цим створила від імені звичайного користувача. Потім вона повинна помістити копію у домашній каталог звичайного користувача.
Далі, використовуючи звичайний обліковий запис, програма намагається змінити файл і зберегти зміни. Що відбудеться?
Після цього програма намагається видалити цей файл за допомогою команди rm. Що відбудеться?

## [Програмний код](3.c)

## Опис:

Створено програму, яка створює папку як користувач (звичайний) далі як root копіює її у домашню теку
користувача, де від імені юзера намагається його змінити, а потім видалити. Результатом таких спроб є
те, що змінення файлу не виходить, оскільки права на зміну належать власнику файлу, тут - корневий.
Проте видалення через rm виходить, тому що право на видалення файлу визначається правами на директорію,
в якій він лежить (тут - домашня папка юзера), тобто користувач може її видаляти. Через те, що простий
юзер намагається видалити захищений файл, так ще й не свій, rm видає повідомлення для підтвердження цієї
дії. Зміна між юзером та рутом організована у коді шляхом редагування та переміщення файлів за допомогою
консольних команд, запущених через system() у коді, або з sudo або без.

## Результат виконання:

```
max@aspz:~/c/9 $ gcc -Wall 3.c -o 3
max@aspz:~/c/9 $ ./3
Creating as user...
-rw-r--r--  1 max wheel 17 May 16 19:57 /tmp/original.txt
Copying to max's home as root...
-r--r--r--  1 root wheel 17 May 16 19:57 /home/max/copied.txt
Editing as user...
sh: cannot create /home/max/copied.txt: Permission denied
Didn't edit
Deleting as user...
override r--r--r-- root/wheel for /home/max/copied.txt?
Deleted
max@aspz:~/c/9 $
```

# Завдання 4

## Умова:

Напишіть програму, яка по черзі виконує команди whoami та id, щоб перевірити стан облікового запису користувача, від імені якого вона запущена.
Є ймовірність, що команда id виведе список різних груп, до яких ви належите. Програма повинна це продемонструвати.

## [Програмний код](4.c)

## Опис:

Написано програму, яка запускає спочатку команду whoami, а потім id для перевірки статусу користувача,
обидві з яких запущено через system(). Клманда whoami (who-am-i, або хто-я) виводить лише ім'я поточного
користувача, а id окрім ім'я (у дужках) виводить user id, group id, та список груп, у яких я знаходжуся.

## Результат виконання:

```
max@aspz:~/c/9 $ gcc -Wall 4.c -o 4
max@aspz:~/c/9 $ ./4
---whoami---:
max

---id---:
uid=1001(max) gid=1001(max) groups=1001(max),0(wheel),44(video)
max@aspz:~/c/9 $
```

# Завдання 5

## Умова:

Напишіть програму, яка створює тимчасовий файл від імені звичайного користувача. Потім від імені суперкористувача використовує команди chown і chmod, щоб змінити тип володіння та права доступу.
Програма повинна визначити, в яких випадках вона може виконувати читання та запис файлу, використовуючи свій обліковий запис.

## [Програмний код](5.c)

## Опис:

Розроблена програма за допомогою system() створює тимчасовий (у /tmp/) файл testperm.txt, права якого потім від
імені адміна (за допомогою sudo у system()) chown (change owner) та chmod (change mod) для зміни власника на root
та прав доступу на 640 (6 - власник може читати та редагувати, 4 - група може читати, 0 - інші не мають доступу).
Далі протестована користувачем max, від імені якого програма далі намагається прочитати цей файл, а потім
відредагувати. Як видно у результатах, читання виходить, оскільки max знаходиться у wheel (адмінівська група), але
не є адміністратором (адмін root є власником цього файлу), через що редагування не виходить. Виводиться cannot create
file при спробі редагування, оскільки юзер не помічає файлу для редагування, і думає що його треба створити, що у
нього не виходить. id запущено для показу груп max (а саме wheel).

## Результат виконання:

```
max@aspz:~/c/9 $ gcc -Wall 5.c -o 5
max@aspz:~/c/9 $ ./5
Creating as user...
-rw-r--r--  1 max wheel 8 May 16 20:32 /tmp/testperm.txt
Making root owner, perms 640...
-rw-r-----  1 root wheel 8 May 16 20:32 /tmp/testperm.txt
Checking read as user max...
Read ok
Checking write as user max...
sh: cannot create /tmp/testperm.txt: Permission denied
No write
max@aspz:~/c/9 $ id
uid=1001(max) gid=1001(max) groups=1001(max),0(wheel),44(video)
max@aspz:~/c/9 $
```

# Завдання 6

## Умова:

Напишіть програму, яка виконує команду ls -l, щоб переглянути власника і права доступу до файлів у своєму домашньому каталозі, в /usr/bin та в /etc.
Продемонструйте, як ваша програма намагається обійти різні власники та права доступу користувачів, а також здійснює спроби читання, запису та виконання цих файлів.

## [Програмний код](6.c)

## Опис:

Побудована програма для перегляду файлів у домашньому каталозі, usr/bin та etc шляход виконання ls -l через
system() (вивід для bin та etc обмежено до 10 рядків бо там дуже багато файлів). Також реалізовано перевірку
прав доступу у різних файлах, обраних навмання, у цих папках за допомогою перевірки -r (read), -w(write), та
-x(execute) прав шляхом виконання консольної команди, запущеною від імені (-u) користувача, яка тестує
([ -r/w/x шлях ]) читабельність/писабельність/виконуваність файлу по черзі та виводить результат.

## Результат виконання:

```
max@aspz:~/c/9 $ gcc -Wall 6.c -o 6
max@aspz:~/c/9 $ ./6
-----home:-----
total 326796
drwxr-xr-x   3 max  max            512 May  5 19:29 Desktop
drwxr-xr-x   2 max  max            512 Feb 16 22:18 Documents
drwxr-xr-x   2 max  max            512 Mar 22 17:01 Downloads
drwxr-xr-x   2 max  max            512 Feb 16 22:18 Music
drwxr-xr-x   3 max  max            512 Feb 20 14:47 Pictures
drwxr-xr-x   2 max  max            512 Feb 16 22:18 Public
drwxr-xr-x   2 max  max            512 Feb 16 22:18 Templates
drwxr-xr-x   2 max  max            512 Feb 16 22:18 Videos
-rw-------   1 max  max   274942218240 May 16 09:50 baloo_file.core
-rw-------   1 max  max       45649920 Feb 19 21:33 baloo_file_extracto.core
drwxr-xr-x  11 max  max            512 May 16 17:28 c
-rw-------   1 max  max      824778752 May  5 18:10 code-oss.core
-r--r--r--   1 root wheel           17 May 16 19:57 copied.txt
-rw-------   1 max  max       46833664 May  5 22:45 drkonqi.core
-rw-------   1 max  max       45834240 May  5 22:45 kded5.core
-rw-r--r--   1 max  max             10 May 16 21:17 mytestfile
drwxrwxrwx   1 root wheel         4096 May 16 13:33 shrd

-----/usr/bin:-----
total 954788
-r-xr-xr-x   1 root wheel         70 Nov 29 12:22 CC
-r-xr-xr-x   3 root wheel     105416 Nov 29 12:24 Mail
-r-xr-xr-x   1 root wheel      86576 Nov 29 12:25 addr2line
-r-xr-xr-x  15 root wheel         74 Nov 29 12:21 alias
-r-xr-xr-x   1 root wheel      10672 Nov 29 12:21 apply
-r-xr-xr-x   4 root wheel     513696 Nov 29 12:22 apropos
-r-xr-xr-x   2 root wheel      50520 Nov 29 12:25 ar
-r-xr-xr-x   1 root wheel       7824 Nov 29 12:21 asa
-r-xr-xr-x   1 root wheel     112544 Nov 29 12:15 asn1_compile

-----/etc:-----
total 808
drwxr-xr-x  2 root wheel      512 Nov 29 11:54 X11
lrwxr-xr-x  1 root wheel       12 Nov 29 12:42 aliases -> mail/aliases
drwxr-xr-x  2 root wheel      512 Nov 29 11:54 authpf
-rw-r--r--  1 root wheel      151 Nov 29 12:25 auto_master
drwxr-xr-x  2 root wheel      512 Nov 29 12:25 autofs
-rw-r--r--  1 root wheel      379 Nov 29 12:25 blacklistd.conf
drwxr-xr-x  2 root wheel      512 Nov 29 12:26 bluetooth
drwxr-xr-x  2 root wheel      512 Nov 29 12:24 cron.d
-rw-r--r--  1 root wheel      646 Nov 29 12:22 crontab

/etc/passwd:
User max can:
+ read
- write
- exec

/usr/bin/ls:
User max can:
- read
- write
- exec

/usr/bin/top:
User max can:
+ read
- write
+ exec

/home/max/mytestfile:
User max can:
+ read
+ write
- exec
max@aspz:~/c/9 $
```

# Завдання 7 (варіант 18)

## Умова:

Побудуйте сценарій, де користувач має доступ до конфіденційної інформації через тимчасові файли.

## [Програмний код](7.c)

## Опис:

У написаній програмі створюється тимчасовий файл SecretXXX (XXX міняються на випадкові символи
через mkstemp),у який записується текст, після чого права доступу змінюються на конфіденційні
(chmod 600: 6 - користувач може писати і читати, 0, 0 - група та інші не мають доступу). Далі
ці дані читаються за допомогою cat, запущеним через system(), що виводить їх на екран. Зберігання
важливих даних у тимчасових файлах несе з собою ризики, оскільки під час виконання програма може
дропнутись, що призведе до невидалення тимчасового файлу з важливими даними, або якщо chmod не
застосується, або перед тим як він виконався дані є вразливими до безперешкодного доступу.

## Результат виконання:

```
ax@aspz:~/c/9 $ gcc -Wall 7.c -o 7
max@aspz:~/c/9 $ ./7
Created: /tmp/secretxvC
Data written
Perms /tmp/secretxvC limited (600).

Reading (cat):
This is top secret

File /tmp/secretxvC deleted
max@aspz:~/c/9 $
```
