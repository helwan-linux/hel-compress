# Helwan Compress (hel-compress)

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
