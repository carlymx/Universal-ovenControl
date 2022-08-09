

### NTC3950 (100KOmh/25ºC) (-50 a 260ºC)

- Calculadoras:
 - Multi Calculadora: https://tinyurl.com/SSH-MultiCalculator
 - Calculadora Coeficientes: https://tinyurl.com/SHH-Calculator

- Tutorial: https://www.instructables.com/Ejemplo-b%C3%A1sico-de-termistor-NTC-y-Arduino/

---

El número 3950 viene de la constante B que se usa en la fórmula para calcular la temperatura absoluta:

R = R 0 x exp ( B ) x (1 / T - 1 / T 0 )

Donde R es la resistencia sensada, R0 es la resistencia sensada a la temperatura T0 (en Kelvin). Como este sensor tienen una resistencia de 100K a 25ºC (323K) la fórmula se puede reducir a:

T = 3950 / ln (R / {100000 xe (-3950 / 323) }) , donde T esta en Kelvin.

