# Helwan Compress (hel-compress)

# Helwan Compress (hel-compress)

An advanced compression and archiving tool supporting multiple compression algorithms, secure encryption, a flexible command-line interface, and an easy-to-use graphical interface.

---

## 🚀 Key Features

* **Multiple Compression Algorithms:** Supports `Zlib`, `Gzip`, `Bzip2`, and `Zstd`.
* **Strong Encryption:** Supports `AES-256-CBC` encryption for data and files.
* **Graphical Interface (GUI):** A GTK+3 graphical interface in English, designed to make the tool easy to use for regular users.
* **Multilingual Command-Line Support:** Understands compression and decompression commands in Arabic, English, Spanish, Chinese, French, and German.

---

## 💻 Command-Line Usage

General command syntax:

```bash
hel-compress <Command> <Input> [Output] [Options]
```

### 1. Compression

The following keywords can be used for compression:

`compress`, `ضغط`, `comprimir`, `压缩`, `compresser`, `komprimieren`

**Compress a regular file:**

```bash
hel-compress compress input.txt output.hc --algo=zstd
```

**Compress a directory:**

```bash
hel-compress --compress-dir my_folder archive.hc --algo=zstd --encrypt
```

### 2. Decompression / Extraction

The following keywords can be used for decompression:

`decompress`, `فك`, `descomprimir`, `解压`, `decompresser`, `entpacken`

**Decompress a file:**

```bash
hel-compress decompress output.hc result.txt --decrypt
```

**Extract a complete archive:**

```bash
hel-compress --extract archive.hc extracted_folder/
```

### 3. Options

```text
--algo=gzip    Use Gzip compression
--algo=bzip2   Use Bzip2 compression
--algo=zstd    Use Zstd compression
--encrypt      Enable AES-256 encryption
--decrypt      Decrypt the data
```

---

## 🖥️ Graphical Interface (GUI)

Helwan Compress includes a complete GTK+3 graphical interface in English, allowing regular users to compress, decompress, and manage archives without using the command line.

Because the package integrates with the desktop environment and provides a Desktop Entry, you can launch **Helwan Compress** directly from your application menu.

---

## 🛠️ Building & Installation

### Arch Linux — Using PKGBUILD

```bash
makepkg -si
```

### Manual Build & Installation

```bash
make
sudo make install
```



أداة متقدمة للضغط والأرشفة مدعومة بخوارزميات متعددة، وتشفير آمن، مع واجهة سطر أوامر مرنة وواجهة رسومية سهلة الاستخدام.

---

## 🚀 المميزات الرئيسية

* **خوارزميات متعددة:** يدعم `Zlib` و`Gzip` و`Bzip2` و`Zstd`.
* **تشفير قوي:** يدعم تشفير `AES-256-CBC` للبيانات والملفات.
* **واجهة رسومية (GUI):** واجهة مستخدم رسومية مبنية بـ GTK+3 باللغة الإنجليزية لسهولة الاستخدام.
* **دعم متعدد اللغات لسطر الأوامر:** يفهم أوامر الضغط والفك باللغات العربية، الإنجليزية، الإسبانية، الصينية، الفرنسية، والألمانية.

---

## 💻 الاستخدام من سطر الأوامر (Terminal)

الصيغة العامة للأمر:

```bash
hel-compress <Command> <Input> [Output] [Options]
```

### 1. أوامر الضغط (Compress)

يمكن استخدام الكلمات المفتاحية التالية:

`compress`, `ضغط`, `comprimir`, `压缩`, `compresser`, `komprimieren`

**ضغط ملف عادي:**

```bash
hel-compress ضغط input.txt output.hc --algo=zstd
```

**ضغط مجلد كامل:**

```bash
hel-compress --compress-dir my_folder archive.hc --algo=zstd --encrypt
```

### 2. أوامر فك الضغط والاستخراج (Decompress / Extract)

يمكن استخدام الكلمات المفتاحية التالية:

`decompress`, `فك`, `descomprimir`, `解压`, `decompresser`, `entpacken`

**فك ضغط ملف:**

```bash
hel-compress فك output.hc result.txt --decrypt
```

**استخراج أرشيف كامل:**

```bash
hel-compress --extract archive.hc extracted_folder/
```

### 3. الخيارات

```text
--algo=gzip    استخدام خوارزمية Gzip
--algo=bzip2   استخدام خوارزمية Bzip2
--algo=zstd    استخدام خوارزمية Zstd
--encrypt      تفعيل تشفير AES-256
--decrypt      فك التشفير
```

---

## 🖥️ الواجهة الرسومية (GUI)

يحتوي البرنامج على واجهة رسومية كاملة مبنية بـ GTK+3 وباللغة الإنجليزية، لتسهيل العمل على المستخدم العادي دون الحاجة إلى استخدام سطر الأوامر.

لتشغيل الواجهة الرسومية، ابحث عن **Helwan Compress** في قائمة التطبيقات الخاصة ببيئة سطح المكتب وشغّله بضغطة زر.

---

## 🛠️ البناء والتثبيت (Building & Installation)

### Arch Linux — باستخدام PKGBUILD

```bash
makepkg -si
```

### البناء والتثبيت اليدوي باستخدام Make

```bash
make
sudo make install
```
