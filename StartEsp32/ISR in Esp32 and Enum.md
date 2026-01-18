

## 1️⃣ ما هي الـ ISR؟

**ISR** اختصار لـ **Interrupt Service Routine**

### المعنى البسيط:

- المقاطعة (**Interrupt**) هي إشارة مفاجئة تصل للمعالج أثناء عمله، تقول له:
    

> "أوقف ما تفعله الآن وتعامل مع هذا الحدث فورًا!"

- **ISR** هي الدالة أو الكود الذي يتم تنفيذه **عند حدوث المقاطعة**.
    

---

### مثال حياتي:

تخيل أنك تعمل على جهاز كمبيوتر:

- أنت تكتب مستند.
    
- فجأة، يرن الهاتف.
    
- تتوقف عن الكتابة للحظة لتجيب على الهاتف، ثم تعود للكتابة.
    

**الهاتف = المقاطعة (Interrupt)**  
**الإجابة على الهاتف = ISR (Interrupt Service Routine)**

---

## 2️⃣ خصائص الـ ISR:

1. **تعمل بشكل فوري** عند حدوث المقاطعة.
    
2. **يجب أن تكون قصيرة جدًا وسريعة**.
    
3. لا تستخدم فيها دوال ثقيلة أو معقدة مثل `delay()` أو `Serial.print()` (على بعض المعالجات).
    
4. عادةً تستخدم لتغيير متغير سريع (`volatile`) أو تشغيل حدث صغير.
    

---

## 3️⃣ كيف تُكتب ISR على Arduino / ESP32؟

```C
volatile int counter = 0; // متغير مشترك بين ISR و loop

void myISR() {  // هذه هي ISR
  counter++;    // مجرد زيادة عدد، سريع جدًا
}

void setup() {
  pinMode(2, INPUT_PULLUP);  // زر
  attachInterrupt(digitalPinToInterrupt(2), myISR, FALLING); // ربط الزر بالمقاطعة
}

void loop() {
  // نستخدم المتغير الذي غيّرته ISR
  Serial.println(counter);
  delay(1000);
}

```

---

4️⃣ توضيح الوسائط في attachInterrupt:

```C
attachInterrupt(pin, ISR, mode);

```

---

| الوسيط | الشرح                              |
| ------ | ---------------------------------- |
| `pin`  | رقم البن الذي سنراقبه للمقاطعة     |
| ISR    | اسم الدالة التي ستنفذ عند المقاطعة |
| mode   | نوع المقاطعة (متى تحدث)            |

### أنواع الـ mode:

1. **LOW**: عندما يكون البن في حالة LOW.
    
2. **CHANGE**: عندما يتغير البن من HIGH إلى LOW أو العكس.
    
3. **RISING**: عند الانتقال من LOW إلى HIGH.
    
4. **FALLING**: عند الانتقال من HIGH إلى LOW.
   
   ---
   ## 5️⃣ قواعد مهمة عند كتابة ISR:

1. **استخدم فقط متغيرات `volatile`**:
    
    - لأن ISR يمكن أن تغير القيم في أي وقت.
```C
volatile bool flag = false;
void myISR() { flag = true; }
```

- **لا تستخدم دوال ثقيلة أو `delay()`**.
    
- **لا تستخدم `Serial.print()` مباشرة في ISR**:
    
    - لأنه يمكن أن يعلق البرنامج أو يسبب مشاكل.
      
      ---
      ## 6️⃣ مثال عملي صغير جدًا:

مثال: عند الضغط على زر، نشعل LED مؤقتًا بدون `delay()`:

```C
#define LED 13
#define BTN 2

volatile bool ledFlag = false;

void toggleLED() { 
  ledFlag = !ledFlag; // نغير حالة LED
}

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(BTN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BTN), toggleLED, FALLING);
}

void loop() {
  digitalWrite(LED, ledFlag); // نشغل أو نوقف LED
}

```

✅ هنا:

- الزر يسبب **مقاطعة**.
    
ا- ISR `toggleLED()` فقط تغير حالة المتغير `ledFlag`.
    
- الـ `loop()` يشغل أو يوقف الـ LED بناءً على هذا المتغير.
  
  ---
  
  ### 7️⃣ وظائف ومفاهيم مرتبطة بالـ ISR:

| الدالة / المفهوم               | الشرح                                                           |
| ------------------------------ | --------------------------------------------------------------- |
| `attachInterrupt()`            | ربط مقاطعة بالبن ودالة ISR                                      |
| `detachInterrupt()`            | إلغاء المقاطعة على البن                                         |
| `digitalPinToInterrupt(pin)`   | تحويل رقم البن إلى رقم المقاطعة الصحيح                          |
| `volatile`                     | كلمة أساسية لضمان أن المتغيرات التي تغير في ISR تُقرأ بشكل صحيح |
| `FALLING, RISING, CHANGE, LOW` | نوع المقاطعة                                                    |
  