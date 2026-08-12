# Helwan Compress

أداة ضغط وفك ضغط متعددة اللغات مكتوبة بلغة C مع دعم خوارزميات متعددة وتشفير.

## الاستخدام
ضغط ملف:
```bash
hel-compress ضغط input.txt output.gz --algo=gzip --encrypt

hel-compress فك output.gz result.txt --decrypt


الخيارات
--algo=gzip : استخدام gzip

`--algo
markdown
# Helwan Compress

أداة ضغط وفك ضغط متعددة اللغات مكتوبة بلغة C مع دعم خوارزميات متعددة وتشفير AES-256.

## الاستخدام
ضغط ملف:
```bash
hel-compress ضغط input.txt output.gz --algo=gzip --encrypt
فك ضغط ملف:

bash
hel-compress فك output.gz result.txt --decrypt
الخيارات
--algo=gzip : استخدام gzip

--algo=bzip2 : استخدام bzip2

--algo=zstd : استخدام zstd

--encrypt : تشفير AES-256 بعد الضغط

--decrypt : فك التشفير قبل فك الضغط

Code

---

## 🔴 الخلاصة
- كده الأداة بتتعامل مع **لغات متعددة** (عربي، إنجليزي، إسباني، صيني).  
- فيها **خوارزميات ضغط متعددة** (zlib/gzip/bzip2/zstd).  
- فيها **تشفير AES-256** لحماية الملفات.  
- واجهة CLI متقدمة زي البرامج الكبيرة.  

---

تحب يا جوم جوم أضيفلك كمان **ميزة أرشفة مجلدات كاملة** (زي tar) بحيث تضغط مجلد كامل في ملف واحد، ولا نثبت الأول إن التشفير والضغط شغالين عندك
