# 🎨 FRACT-OL PROJESİ - EVALUATION REHBERI

## İÇİNDEKİLER
1. [Proje Özeti](#proje-özeti)
2. [Dosya Yapısı](#dosya-yapısı)
3. [Detaylı Konu Anlatımı](#detaylı-konu-anlatımı)
4. [Teknik Derinlemesine](#teknik-derinlemesine)
5. [Sık Sorulan Sorular](#sık-sorulan-sorular)

---

## PROJE ÖZETI

**FRACT-OL** = Mandelbrot ve Julia fraktallarını gerçek zamanlı olarak görselleştiren etkileşimli grafik uygulaması.

**Ana Özellikler:**
- ✅ Mandelbrot Set görselleştirme
- ✅ Julia Set (parametrik) görselleştirme
- ✅ Mouse zoom in/out
- ✅ Smooth renk gradyanı
- ✅ Event-driven interaktif sistem
- ✅ Bonus: mouse pan ve ekstra zoom özellikleri

**Teknoloji Stack:**
- Dil: C (C89/C99)
- Grafik: minilibx (X11 wrapperi)
- İşletim Sistemi: Linux
- Build: Makefile

---

## DOSYA YAPISI

```
fract-ol/
├── main.c                    # Giriş noktası, komut satırı parsing
├── fractol.h                 # Header, struct tanımları
├── setup_mlx.c               # X11/minilibx kurulumu
├── drawing_fractal.c         # Fraktal çizim algoritması
├── math_utils.c              # Kompleks sayı matematik
├── libft_stuff.c             # Utility fonksiyonlar
├── Makefile                  # Build sistemi
├── minilibx-linux/           # Grafik kütüphanesi
│
├── (BONUS VERSİYON)
├── main_bonus.c
├── setup_mlx_bonus.c
├── drawing_fractal_bonus.c
├── math_utils_bonus.c
├── libft_stuff_bonus.c
├── mouse_zoom_bonus.c
├── mouse_move_bonus.c
└── fractol_bonus.h
```

---

## DETAYLI KONU ANLATIMI

### 1. RENK HESABI (Color Calculation)

#### Kod:
```c
static int get_color(int iter, int max_iter)
{
    int r, g, b;
    double t;
    
    t = (double)iter / max_iter;      // 0.0 - 1.0 arasında normalize
    if (iter == max_iter)
        return (0x000000);             // Siyah (set içinde)
    
    r = (int)(9 * t * 255) % 256;
    g = (int)(15 * t * 255) % 256;
    b = (int)(30 * t * 255) % 256;
    return ((r << 16) | (g << 8) | b);
}
```

#### Detaylı Açıklama:

**Adım 1: Normalizasyon**
```
t = iter / max_iter

Örnek (max_iter = 100):
- iter = 0  → t = 0.00   (çok hızlı diverge)
- iter = 25 → t = 0.25   (hızlı diverge)
- iter = 50 → t = 0.50   (orta)
- iter = 75 → t = 0.75   (yavaş diverge)
- iter = 100 → t = 1.00  (set içinde)
```

**Adım 2: Renk Kanalları**
```
R (Kırmızı):   r = (int)(9 * t * 255) % 256
G (Yeşil):     g = (int)(15 * t * 255) % 256
B (Mavi):      b = (int)(30 * t * 255) % 256

Neden farklı çarpanlar (9, 15, 30)?
→ Her kanal farklı hızda artar
→ Güzel gradient efekti yaratır
```

**Örnek:**
```
t = 0.1 olsun:
  r = (int)(9 * 0.1 * 255) % 256 = 22    → 0x16
  g = (int)(15 * 0.1 * 255) % 256 = 38   → 0x26
  b = (int)(30 * 0.1 * 255) % 256 = 76   → 0x4C
  
  Renk = 0x16264C (koyu turuncu)

t = 0.5 olsun:
  r = (int)(9 * 0.5 * 255) % 256 = 127   → 0x7F
  g = (int)(15 * 0.5 * 255) % 256 = 191  → 0xBF
  b = (int)(30 * 0.5 * 255) % 256 = 127  → 0x7F
  
  Renk = 0x7FBF7F (açık yeşil)
```

**Adım 3: Hex Formatına Çevirme (0xRRGGBB)**
```
r = 0x7F, g = 0xBF, b = 0x7F

r << 16 = 0x7F0000  (R'yi 16 bit sola kaydır)
g << 8  = 0x00BF00  (G'yi 8 bit sola kaydır)
b       = 0x00007F

OR işlemi: 0x7FBF7F
```

**Neden % 256?**
```
Taşma (overflow) önleme:
- 9 * 1.0 * 255 = 2295
- 2295 % 256 = 247 (max: 0xFF)
- Güvenli range içinde kalır
```

**Sonuç:** Diverge hızına göre smooth gradient (kırmızı → yeşil → mavi)

---

### 2. MANDELBROT SET

#### Matematiğe Giriş

**Tanım:**
$$z_{n+1} = z_n^2 + c$$

**Mandelbrot Set kuralı:**
- Başlangıç: $z_0 = 0$ (HER ZAMAN)
- Parametre: $c = pixel$ (değişken)
- Koşul: Eğer $|z_n| > 2$ ise diverge (set'te değil)
- Seti: $|z_n| \leq 2$ kalan tüm $c$ değerleri

#### Kod:
```c
int mandelbrot_iter(t_complex c)
{
    t_complex z;
    int iter;
    
    z.re = 0.0;                    // z₀ = 0
    z.im = 0.0;
    iter = 0;
    
    while (iter < MAX_ITER)
    {
        if ((z.re * z.re + z.im * z.im) > 4.0)  // |z|² > 4
            return (iter);
        z = complex_square(z);     // z = z²
        z.re += c.re;              // z = z² + c
        z.im += c.im;
        iter++;
    }
    return (MAX_ITER);
}
```

#### Adım Adım Örnek

Pixel (x=100, y=150) için c hesapla:
```
Screen koordinat → Math koordinat:
re = -2.0 + (4.0) * (100 / 600) = -2.0 + 0.667 = -1.333
im = -2.0 + (4.0) * (150 / 600) = -2.0 + 1.0 = -1.0

c = -1.333 - 1.0i
```

Iterasyon:
```
z₀ = 0 + 0i
|z₀|² = 0 < 4 ✓

z₁ = (0)² + (-1.333 - 1.0i) = -1.333 - 1.0i
|z₁|² = 1.777 + 1.0 = 2.777 < 4 ✓

z₂ = (-1.333 - 1.0i)² + (-1.333 - 1.0i)
   = (1.777 - 1.0 + 2*(-1.333)*(-1.0)i) + (-1.333 - 1.0i)
   = (0.777 + 2.666i) + (-1.333 - 1.0i)
   = -0.556 + 1.666i
|z₂|² = 0.309 + 2.777 = 3.086 < 4 ✓

z₃ = (-0.556 + 1.666i)² + (-1.333 - 1.0i)
   = (0.309 - 2.777 + 2*(-0.556)*(1.666)i) + (-1.333 - 1.0i)
   = (-2.468 - 1.853i) + (-1.333 - 1.0i)
   = -3.801 - 2.853i
|z₃|² = 14.45 + 8.14 = 22.59 > 4 ✗ DIVERGED

Sonuç: iter = 3 → renk hesaplanır
```

#### Neden |z| > 2 kontrolü?

Matematik teorisi: Eğer $|z_n| > 2$ ise mutlaka diverge eder
```
Kanıt:
|z_{n+1}| = |z_n² + c| ≥ |z_n²| - |c|
          = |z_n|² - 2
          
z₀ > 2 ise:
|z₁| ≥ |z₀|² - 2 > 4 - 2 = 2
(geometrik olarak büyümeye devam eder)
```

---

### 3. JULIA SET

#### Matematiğe Giriş

**Tanım:**
$$z_{n+1} = z_n^2 + c$$

**Julia Set kuralı:**
- Başlangıç: $z_0 = pixel$ (değişken, HER PIXEL FARKLI)
- Parametre: $c = sabit$ (kullanıcı input)
- Koşul: $|z_n| > 2$ ise diverge

#### Kod:
```c
int julia_iter(t_complex z, t_complex c)
{
    int iter;
    
    iter = 0;
    while (iter < MAX_ITER)
    {
        if ((z.re * z.re + z.im * z.im) > 4.0)
            return (iter);
        z = complex_square(z);
        z.re += c.re;              // z = z² + c
        z.im += c.im;
        iter++;
    }
    return (MAX_ITER);
}
```

#### Mandelbrot vs Julia - Karşılaştırma

| Özellik | Mandelbrot | Julia |
|---------|-----------|-------|
| z₀ | 0 (sabit) | pixel (değişken) |
| c | pixel (değişken) | sabit parametre |
| Başında | Hep 0'dan başla | Her pixel başında farklı |
| Parametresi | Yok | -0.7+0.27i vb. |
| Görüntü | Tek set | Parametre bağlı |

#### Örnek: Julia c = -0.7 + 0.27i

```
Pixel (100, 150) → z₀ = -1.333 - 1.0i
z₁ = (-1.333 - 1.0i)² + (-0.7 + 0.27i)
z₂ = z₁² + (-0.7 + 0.27i)
...
c ASLA DEĞİŞMEZ, z DEĞİŞİR

Pixel (101, 150) → z₀ = -1.330 - 1.0i (biraz farklı)
z₁ = (-1.330 - 1.0i)² + (-0.7 + 0.27i)
z₂ = z₁² + (-0.7 + 0.27i)
...
c HALA AYNI, z İLE BAŞLANGICI FARKLI
```

---

### 4. KOMPLEKS SAYI KARESI

#### Matematiğe Giriş

$$(a + bi)^2 = a^2 + 2abi + (bi)^2$$
$$= a^2 + 2abi - b^2$$
$$= (a^2 - b^2) + 2ab·i$$

#### Kod:
```c
t_complex complex_square(t_complex z)
{
    t_complex result;
    
    result.re = z.re * z.re - z.im * z.im;    // Real part
    result.im = 2.0 * z.re * z.im;             // Imaginary part
    return (result);
}
```

#### Örnek Hesap

z = 3 + 4i

```
Re = 3² - 4² = 9 - 16 = -7
Im = 2 * 3 * 4 = 24

z² = -7 + 24i ✓

Doğrulama: (3 + 4i)² = 9 + 24i + 16i² = 9 + 24i - 16 = -7 + 24i ✓
```

---

### 5. BUFFER VE BPP (Bits Per Pixel)

#### Bellek Yönetimi

Ekran = 2D dizi, ancak bellek = lineer!

```
Ekran (600×600):
(0,0)   (1,0)   (2,0)  ...  (599,0)
(0,1)   (1,1)   (2,1)  ...  (599,1)
...
(0,599) (1,599) (2,599) ... (599,599)

Bellek (lineer):
[pix(0,0)][pix(1,0)][pix(2,0)]...[pix(599,0)]
[pix(0,1)][pix(1,1)][pix(2,1)]...[pix(599,1)]
...
```

#### Adres Hesabı

```c
put_pixel(t_fractol *f, int x, int y, int color)
{
    char *dst;
    
    // KRITIK FORMÜL:
    dst = f->img.addr + (y * f->img.line_len + x * (f->img.bpp / 8));
    
    *(unsigned int *)dst = color;
}
```

**Formül Parçalama:**

```
offset = y * line_len + x * (bpp / 8)

y * line_len      = "Kaçıncı satıra gidilecek?"
                    Her satır line_len byte
                    Örnek: 600 pixel * 4 byte = 2400 byte
                    
x * (bpp / 8)     = "Satırda kaç byte ileri gidilecek?"
                    bpp = 32 (32 bit per pixel)
                    bpp / 8 = 4 byte per pixel
                    x=100 ise 100 * 4 = 400 byte

Örnek: Pixel (100, 150)
offset = 150 * 2400 + 100 * 4
       = 360000 + 400
       = 360400 byte
```

**Cast `(unsigned int *)`**

```c
char *dst;              // 1 byte
*(unsigned int *)dst    // 4 byte yazılacak

Neden?
- Color = 0xRRGGBB = 4 byte (32 bit)
- char* 1 byte yazardı
- unsigned int* 4 byte yazıyor
```

---

### 6. X11 ve GRAFİK SUNUCUSU

#### X11 Mimarisi

```
┌─────────────────────────────────┐
│   Senin Uygulanması (Client)    │
│  (fractol executable)           │
└────────────┬────────────────────┘
             │
             │ mlx_init(), mlx_new_window(), vb.
             │
             ↓
┌─────────────────────────────────┐
│    X11 Server                   │
│  (Linux çekirdeği)              │
│                                 │
│  - Pencere yönetimi             │
│  - Mouse/Keyboard dinleme       │
│  - Display işleme               │
└────────────┬────────────────────┘
             │
             ↓
    [Monitor / Ekran]
```

#### Neden X11?

1. **Network Transparency:** SSH üzerinden bile grafik gönderilebilir
2. **Merkezi Yönetim:** Bir X11 sunucusu birden fazla uygulamayı yönetebilir
3. **Resource Sharing:** Pencereler, fontlar, vb. paylaşılır

#### minilibx Abstraksiyonu

minilibx, X11'i C fonksiyonlarına basitleştirmiştir:

```c
// Direkt X11 (karmaşık):
Display *dpy = XOpenDisplay(NULL);
int screen = DefaultScreen(dpy);
Window win = XCreateWindow(dpy, RootWindow(dpy, screen), ...);
// ... 100+ satır ...

// minilibx (basit):
void *mlx = mlx_init();
void *win = mlx_new_window(mlx, 600, 600, "fractol");
```

#### Handle Sistemi

```c
void *mlx = mlx_init();
// X11'e: "Merhaba, ben bir grafik uygulamasıyım"
// X11: "Tamam, senin connection ID'n = 0x12345678"
// mlx'in pointer'ı = 0x12345678

void *win = mlx_new_window(mlx, 600, 600, "fractol");
// X11'e (mlx aracılığıyla): "Bu mlx için 600x600 pencere aç"
// X11: "Tamam, pencere ID'n = 0x87654321"

void *img = mlx_new_image(mlx, 600, 600);
// X11'e: "Bir buffer oluştur"
// X11: "Bufferin başlangıç adresi = 0xdeadbeef"
```

---

### 7. EVENT HOOKS (Olay Dinleme)

#### Hook Sistemi

```c
mlx_key_hook(f->win, is_esc, f);
mlx_hook(f->win, 17, 0, destroy_and_exit, f);
mlx_mouse_hook(f->win, mouse_scroll, f);
```

**Hook = Callback (Geri Çağırma)**

```
X11 Olay Döngüsü:
┌────────────────────────────────┐
│ while (true) {                 │
│   event = XNextEvent(...)      │
│   if (event.type == KeyPress) {│
│     ├─ "Bu window'da hook var?"│
│     └─ EVET: is_esc() çağrı    │
│   }                            │
│   if (event.type == MouseBtn) {│
│     ├─ "Bu window'da hook var?"│
│     └─ EVET: mouse_scroll()    │
│   }                            │
│ }                              │
└────────────────────────────────┘
```

#### Event Kodları

| Kod | Olay | Açıklama |
|-----|------|----------|
| 4 | MOUSE_SCROLL_UP | Tekerlek yukarı |
| 5 | MOUSE_SCROLL_DOWN | Tekerlek aşağı |
| 17 | ClientMessage | Pencere kapatma |
| 65307 | KEY_ESC | ESC tuşu |
| 2 | KeyPress | Herhangi bir tuş |

#### Callback Fonksiyonları

```c
// X11 tarafından çağrılır
int is_esc(int keycode, t_fractol *f)
{
    if (keycode == KEY_ESC)
        destroy_and_exit(f);
    return (0);
}

// X11 tarafından çağrılır
int mouse_scroll(int button, int x, int y, t_fractol *f)
{
    if (button == 4)  // Scroll up
        zoom_in(f, x, y);
    else if (button == 5)  // Scroll down
        zoom_out(f, x, y);
    draw_fractal(f);
    return (0);
}

// X11 tarafından çağrılır
int destroy_and_exit(t_fractol *f)
{
    mlx_destroy_image(f->mlx, f->img.img_ptr);
    mlx_destroy_window(f->mlx, f->win);
    mlx_destroy_display(f->mlx);
    free(f->mlx);
    exit(0);
}
```

---

### 8. BIT SHIFT: 1L vs 1LL

#### Veri Tipleri

```c
1L      // long (32 bit)
1LL     // long long (64 bit)
```

#### Bit Shift İşlemi

Bit shift = sayıyı binary olarak kaydırma

```
1 << 0  = 0b00000001 = 1
1 << 1  = 0b00000010 = 2
1 << 2  = 0b00000100 = 4
1 << 8  = 0b100000000 = 256
1 << 16 = 0b10000000000000000 = 65536
```

#### Renk Kodunda Kullanımı

```c
r = 255, g = 128, b = 64

color = (r << 16) | (g << 8) | b

(255 << 16) = 0xFF0000
(128 << 8)  = 0x008000
64          = 0x000040
            = 0xFF8040
```

#### L vs LL Karşılaştırması

```c
// 32-bit (L):
1L << 30 = 0x40000000  (safe)
1L << 31 = 0x80000000  (overflow riski, sign bit)

// 64-bit (LL):
1LL << 62 = 0x4000000000000000  (safe)
1LL << 63 = 0x8000000000000000  (sign bit)
```

#### Bu Projede

```c
r << 16  // r = 0-255, << 16, max = 0xFF0000
g << 8   // g = 0-255, << 8, max = 0x00FF00
b        // b = 0-255, max = 0x0000FF

Toplam = 0xFFFFFF (24-bit yeterli)

Sonuç: L yeterli, LL gereksiz
```

**Tercih:** `L` (daha temiz, LL lazy)

---

### 9. NİYE [-2, 2] ARALIGI?

#### Mandelbrot Set'in Coğrafyası

```
Mandelbrot Set'in tüm ilginç bölgesi:
- Reel eksende: -2 ile +0.5 arasında
- Sanal eksende: -1.25 ile +1.25 arasında

Simetrik bir kısım alıyoruz: [-2, 2] × [-2, 2]
```

#### Görsel Harita

```
        +2i  ┌──────────────────┐
             │ Mandelbrot Set   │
             │                  │
      0i  ───┼──────────────────┼─── 0
             │       (main      │
             │       body)      │
       -2i  └──────────────────┘
            -2        0        +2
            
Şekil: Bulunduğu yer
- Ana gövde ortada
- Spiral kol sağa
- Dış detaylar [-2, 2] içinde
```

#### Neden Dışarısında Hiç İlginç Bir Şey Yok?

```
Teorem: Eğer |c| > 2 ise c Mandelbrot set'te değil

Kanıt:
|z₀| = 0 < 2
|z₁| = |0 + c| = |c| > 2
→ Hemen diverge eder

Sonuç: |c| > 2 ise Mandelbrot'ta olamaz
```

#### Julia Set İçin Fark

```
Julia set'i farklı c değerleri için:

c = -0.7 + 0.27i  → Spiral desenler
c = -0.4 + 0.6i   → Fırın şekli
c = 0.285 + 0.01i → Karmaşık fraktal

Her c için faklı görüntü!
```

---

### 10. ZOOM MEKANIZMASI

#### Zoom In Mantığı

```c
Kullanıcı mouse scroll up (zoom in)
  │
  ├─ Mouse pozisyonu: (x, y) pixel
  ├─ Math alanına çevir: (cx, cy) complex
  ├─ Yeni merkez = (cx, cy)
  │
  ├─ Yeni alanı hesapla (1.5x küçültsün):
  │   width = (max_re - min_re) / 1.5
  │   height = (max_im - min_im) / 1.5
  │
  ├─ min_re = cx - width/2
  │  max_re = cx + width/2
  │  min_im = cy - height/2
  │  max_im = cy + height/2
  │
  └─ draw_fractal() → Yeni alan çizilir
```

#### Örnek Hesap

```
Başlangıç: [-2, 2] × [-2, 2]

Mouse: x=300, y=300 (ortada)
→ Complex: re=-0, im=0

Zoom in (1.5x):
width = 4 / 1.5 = 2.667
height = 4 / 1.5 = 2.667

min_re = 0 - 2.667/2 = -1.333
max_re = 0 + 2.667/2 = +1.333
min_im = 0 - 2.667/2 = -1.333
max_im = 0 + 2.667/2 = +1.333

Yeni alan: [-1.333, 1.333] × [-1.333, 1.333]
```

#### Zoom Out Mantığı

```
Zoom out = faktör < 1

zoom_factor = 0.667 (2/3)

width = 4 * 0.667 = 2.667  (wait, bu aynı?)
        
Hatalı, doğrusu:
width = 4 / 0.667 = 6

min_re = center_re - 3
max_re = center_re + 3
```

---

### 11. mlx_loop SONSUZ DÖNGÜ

#### Başlangıç Sırası

```c
int main(int argc, char **argv)
{
    t_fractol f;
    
    parse_arguments(argc, argv, &f);      // ① Parametreler parse
    init_mlx(&f);                         // ② X11 bağlantı
    mlx_hooks(&f);                        // ③ Event listener'ları kaydet
    draw_fractal(&f);                     // ④ İlk çizim
    mlx_loop(f.mlx);                      // ⑤ SONSUZ DÖNGÜ
    
    return (0);  // ASLA BURAYA GELİNMEZ
}
```

#### mlx_loop İç Yapısı

```c
// minilibx'in içinde (sadece konsept):
void mlx_loop(void *mlx)
{
    XEvent event;
    int running = 1;
    
    while (running)  // Sonsuz döngü
    {
        XNextEvent(dpy, &event);  // Sistem: "Bir olay var mı?"
        
        if (event.type == KeyPress)
            handle_key_event(&event);     // ← Sizin is_esc() çağrılır
        
        else if (event.type == ButtonPress)
            handle_mouse_event(&event);   // ← Sizin mouse_scroll() çağrılır
        
        else if (event.type == ClientMessage)
            handle_destroy(&event);       // ← Sizin destroy_and_exit() çağrılır
                                          //   Bu exit(0) yapar!
    }
}
```

#### minilibx Nedir? (Kütüphane)

```
minilibx = Compiled C library

İçeriği:
- X11 system call wrapper'ları
- Function pointerlar
- Event handling kodu

Derlenmiş hali: minilibx-linux/libmlx.a

Makefile'da linki:
    cc ... -L./minilibx-linux -lmlx -lX11 ...
    ├─ -L: Library dosyalarının yolu
    ├─ -lmlx: libmlx.a'yı link et
    └─ -lX11: X11 system library'si
```

#### System Call vs Library Call

```
System Call:
- İşletim sistemine direkt çağrı
- Çekirdek alanında çalışır
- Örnek: open(), read(), fork()

Library Call:
- Compiled C kodu
- User alanında çalışır
- Örnek: printf(), mlx_init()

minilibx'in yaptığı:
┌─ mlx_init()
├─ dlopen("./minilibx.so")
├─ X11 kütüphanesini yükle
└─ XNextEvent() → system call yapma
   └─ ioctl() → kernel

Sonuç: Kütüphane, sistem çağrılarını çağırır
```

---

### 12. KOORDINAT DÖNÜŞÜMÜ (Ekran → Math)

#### Problem

Ekran ve Math alanı farklı:

```
EKRAN ALANI (pixel):
- x ∈ [0, 600]
- y ∈ [0, 600]
- (0,0) sol üst
- y arttıkça aşağı

MATH ALANI (complex):
- re ∈ [-2, 2]
- im ∈ [-2, 2]
- (-2,-2) sol alt
- im arttıkça yukarı
```

#### Çözüm (Lineer İnterpolasyon)

```
Formül:
math_value = min_math + (max_math - min_math) * (pixel / max_pixel)

Reel eksene:
z.re = -2 + (2 - (-2)) * (x / 600)
     = -2 + 4 * (x / 600)
     = -2 + (4x/600)

Sanal eksene:
z.im = -2 + (2 - (-2)) * (y / 600)
     = -2 + 4 * (y / 600)
     = -2 + (4y/600)
```

#### Doğrulama

```
x=0:    z.re = -2 + 0 = -2      ✓ (sol)
x=300:  z.re = -2 + 2 = 0       ✓ (ortası)
x=600:  z.re = -2 + 4 = 2       ✓ (sağ)

y=0:    z.im = -2 + 0 = -2      ✓ (alt)
y=300:  z.im = -2 + 2 = 0       ✓ (orta)
y=600:  z.im = -2 + 4 = 2       ✓ (üst)
```

#### Zoom Sonrası

```
Zoom in: [-1.333, 1.333] × [-1.333, 1.333]

z.re = -1.333 + (2.667) * (x / 600)
z.im = -1.333 + (2.667) * (y / 600)

x=0:    z.re = -1.333     ✓
x=300:  z.re = 0          ✓
x=600:  z.re = 1.333      ✓
```

---

### 13. t_image STRUCT

#### Tanım

```c
typedef struct s_image
{
    void *img_ptr;    // X11 image handle
    char *addr;       // Pixel buffer başlangıç adresi
    int bpp;          // Bits Per Pixel (32)
    int line_len;     // Satır uzunluğu bytes cinsinden (2400)
    int endian;       // Byte order (0=little, 1=big)
} t_image;
```

#### Detay Açıklaması

**img_ptr:**
```
X11'den dönen handle:
mlx_new_image(mlx, 600, 600)
  └─ "Tamam, image ID'n = 0xdeadbeef"
  
Bu handle ile:
- mlx_destroy_image(mlx, img_ptr)
- mlx_put_image_to_window()
```

**addr:**
```
Pixel buffer'ın bellekteki başlangıç adresi:
mlx_get_data_addr(img_ptr, &bpp, &line_len, &endian)
  └─ "Buffer adresi = 0x12345678"

Bu adresten:
- put_pixel() ile yazılır
```

**bpp (Bits Per Pixel):**
```
Bir pixel kaç bit tutar?

Seçenekler:
- 1 = 1 bit (siyah/beyaz)
- 8 = 8 bit (256 renk)
- 24 = 24 bit (RGB, 16 milyon renk)
- 32 = 32 bit (RGBA, 16 milyon + alpha)

Bu proje: 32 bit
- Byte cinsinden: 32 / 8 = 4 byte per pixel
```

**line_len:**
```
Bir satırın bellekteki uzunluğu (byte cinsinden):

line_len = 600 pixels * 4 bytes/pixel
         = 2400 bytes

Y koordinatı değiştirince:
y'den y+1'e gitmek için offset = 2400 byte ilerle
```

**endian (Byte Sırası):**
```
Sayı 0x12345678'i bellekte nasıl saklanır?

Little Endian (Intel, x86):
Adres:  [0] [1] [2] [3]
Veri:   78  56  34  12
        ↑
        En düşük byte önce

Big Endian (PowerPC, eski):
Adres:  [0] [1] [2] [3]
Veri:   12  34  56  78
        ↑
        En yüksek byte önce

Bu proje: endian = 0 (little endian)
```

---

### 14. t_fractol STRUCT

#### Tanım

```c
typedef struct s_fractol
{
    void *mlx;          // X11 connection handle
    void *win;          // Window handle
    t_image img;        // Pixel buffer yönetimi
    char *fractal_name; // "mandelbrot" | "julia"
    double min_re;      // Sol sınır
    double max_re;      // Sağ sınır
    double min_im;      // Alt sınır
    double max_im;      // Üst sınır
    t_complex julia_c;  // Julia parametresi
} t_fractol;
```

#### State Yönetimi

Bu struct, uygulamanın **tüm durumunu** tutar:

```
Grafik:
├─ mlx: X11'e bağlı kalır
├─ win: Pencere açık tutulur
└─ img: Pixel buffer hazırda

Fraktal:
├─ fractal_name: Hangi set?
├─ min_re, max_re, min_im, max_im: Görünüm alanı
└─ julia_c: Julia parametresi (eğer julia ise)
```

#### Kullanımı

```c
// Zoom in yapıldığında:
t_fractol f;
f.max_re = f.min_re + (f.max_re - f.min_re) / 1.5;
// ... diğer alanlar güncelleme ...
draw_fractal(&f);  // Tüm state kullanılır

// Farklı fraktal çizildiğinde:
if (ft_strncmp(f.fractal_name, "mandelbrot", 11) == 0)
    iter = mandelbrot_iter(z);
else
    iter = julia_iter(z, f.julia_c);  // julia_c referansı
```

---

## TEKNİK DERİNLEMESİNE

### Main Akış (Call Stack)

```
main()
├─ parse_arguments()
│  ├─ ft_strncmp() → "mandelbrot"?
│  └─ ft_atof() → Julia parametrelerini parse
│
├─ init_mlx()
│  ├─ mlx_init() → X11 bağlantısı
│  ├─ mlx_new_window() → Pencere
│  ├─ mlx_new_image() → Buffer
│  ├─ mlx_get_data_addr() → Buffer adresi
│  └─ Başlangıç zoom: [-2, 2]
│
├─ mlx_hooks()
│  ├─ mlx_key_hook() → ESC listener
│  ├─ mlx_hook() → Window close listener
│  └─ mlx_mouse_hook() → Mouse scroll listener
│
├─ draw_fractal()
│  ├─ for y in [0, 600]
│  │  └─ for x in [0, 600]
│  │     ├─ z = koordinat dönüşümü
│  │     ├─ iter = mandelbrot_iter() | julia_iter()
│  │     ├─ color = get_color()
│  │     └─ put_pixel() → buffer'a yaz
│  │
│  └─ mlx_put_image_to_window() → X11'e gönder
│
└─ mlx_loop()
   ├─ XNextEvent() → Olay bekle
   ├─ Event?
   │  ├─ KeyPress ESC → is_esc() → destroy_and_exit()
   │  ├─ MouseWheel up/down → mouse_scroll() → zoom → draw_fractal()
   │  └─ ClientMessage → destroy_and_exit()
   └─ Sonsuz döngü devam eder...
```

### Memory Layout

```
Stack:
┌─────────────────────────────┐
│ main() frame                │
│  - t_fractol f              │ ← Struct
│  - argc, argv               │
└─────────────────────────────┘
│ draw_fractal() frame        │
│  - local vars               │
└─────────────────────────────┘
│ mandelbrot_iter() frame     │
│  - t_complex z, c           │
└─────────────────────────────┘

Heap:
mlx_init() → malloc() → 0x12345678
mlx_new_window() → malloc() → 0x12346000
mlx_new_image() → malloc() → 0x12350000
  ├─ Image metadata
  └─ Pixel buffer (600×600×4 = 1.44MB)

Global:
"mandelbrot" string
"julia" string
"fractol" string
```

### Performance

```
draw_fractal() süresi:

Bölüm 1: Loop (600×600 = 360K iteration)
Bölüm 2: mandelbrot_iter() (max 100 iteration/pixel)
         → 360K × 100 = 36M işlem/frame

Tipik FPS:
- Başlangıç: 5-10 FPS (tüm set)
- Zoom in: 0.5-2 FPS (detay arttıkça, iterasyon artar)

Optimize:
- Daha yüksek max_iter: daha yavaş
- Daha düşük max_iter: daha az detay

Bonus optimizasyon:
- Multi-threading
- SIMD (vectorization)
- GPU computing
```

---

## SIKÇA SORULAN SORULAR

### Q1: Neden z başlangıcı 0, c ise pixel?

**A:** Mandelbrot set tanımı böyle:

$$M = \{c \in \mathbb{C} : \text{orbit of 0 under } f_c(z) = z^2 + c \text{ is bounded}\}$$

"0'dan başlayıp c ile iterasyon yapılan sayılar sınırlı mı?" sorusunun cevabı = Mandelbrot set.

---

### Q2: Julia parametresi nedir? Neden -0.7 + 0.27i?

**A:** 
- Her Julia set bir **c parametresine** bağlı
- c = -0.7 + 0.27i → güzel spiral desenleri oluşturur
- c = -0.4 + 0.6i → "fırın" şekli
- Diğer c değerleri → başka şekiller

Cezaevi tarafından seçilir.

---

### Q3: Buffer'ı neden malloç etmiyorum?

**A:** mlx_new_image() zaten bellek alıyor:
- mlx_new_image() → buffer allocation
- mlx_get_data_addr() → buffer pointer döndür

Siz sadece referansı saklıyorsunuz.

---

### Q4: Renk formülü neden 9, 15, 30?

**A:** Sanat seçimi. Güzel gradient için:
- Tüm kanallar aynı hızda artsaydı: gri
- Farklı hızlar → Rainbow gradient

Alternatif formüller:
```c
r = (int)(5 * t * 255) % 256;
g = (int)(10 * t * 255) % 256;
b = (int)(20 * t * 255) % 256;
```
de çalışır, başka renkler verir.

---

### Q5: Zoom faktörü neden 1.5?

**A:** Rahat zoom hızı:
- 1.1 = çok yavaş zoom
- 1.5 = balanseli
- 2.0 = hızlı zoom

Tercih meselesi.

---

### Q6: Maximum iterasyon neden 100?

**A:** Balance:
- 50 = hızlı ama az detay
- 100 = balanseli
- 1000 = çok detay ama yavaş

Subject gereksinimine göre.

---

## ÖZET

| Konsept | Anahtar Nokta |
|---------|---------------|
| **Renk** | iter/max_iter oranı → gradient |
| **Mandelbrot** | z₀=0, c=pixel |
| **Julia** | z₀=pixel, c=sabit |
| **Buffer** | Lineer bellek, offset hesabı |
| **X11** | Grafik sunucusu, event-driven |
| **Zoom** | Alan daralt, yeniden çiz |
| **Loop** | mlx_loop sonsuz döngü, hooklar callback |
| **Koordinat** | [0,600] → [-2,2] lineer map |

---

**Son Kelime:** Eğer evaluatorda soruştursa, bu dokümantasyon başında en çok gerekli: **hook sistemi, buffer yönetimi ve koordinat dönüşümü**. 🎯

