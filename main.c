/***
 * Timer Shooting
 * By: Adimael Santos da Silva
 * Código disponível em: github.com/adimael
 */
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/timer.h"

#define LED_VERDE 11
#define LED_VERMELHO 12
#define LED_AZUL 13
#define BOTAO 5

bool sequencia_em_execucao = false;  // Impede novas execuções até o final da sequência

// Callback para desligar o LED Azul (primeiro a desligar)
int64_t desligar_led_azul(alarm_id_t id, void *user_data) {
    gpio_put(LED_AZUL, 0);
    sequencia_em_execucao = false;  // Libera o botão para outra sequência
    return 0;
}

// Callback para desligar o LED Verde (último a desligar)
int64_t desligar_led_verde(alarm_id_t id, void *user_data) {
    gpio_put(LED_VERDE, 0);
    add_alarm_in_ms(3000, desligar_led_azul, NULL, false);  // Agendar desligamento do LED Vermelho
    return 0;
}

// Callback para desligar o LED Vermelho (segundo a desligar)
int64_t desligar_led_vermelho(alarm_id_t id, void *user_data) {
    gpio_put(LED_VERMELHO, 0);
    add_alarm_in_ms(3000, desligar_led_verde, NULL, false);  // Agendar desligamento do LED Verde
    return 0;
}


// Inicia a sequência de LEDs
void iniciar_sequencia() {
    sequencia_em_execucao = true;  // Bloqueia novas execuções até a sequência terminar

    // Acender todos os LEDs
    gpio_put(LED_VERDE, 1);
    gpio_put(LED_VERMELHO, 1);
    gpio_put(LED_AZUL, 1);

    add_alarm_in_ms(3000, desligar_led_vermelho, NULL, false);  // Iniciar desligamento do Azul em 3s
}

// Função de debounce do botão
bool debounce_botao() {
    static uint32_t ultimo_tempo = 0;
    uint32_t tempo_atual = to_ms_since_boot(get_absolute_time());

    if (tempo_atual - ultimo_tempo < 50) {  // 50ms de debounce
        return false;
    }

    ultimo_tempo = tempo_atual;
    return true;
}

// Função de interrupção do botão
void pressionar_botao(uint gpio, uint32_t eventos) {
    if (!sequencia_em_execucao && debounce_botao()) {
        iniciar_sequencia();
    }
}

int main() {
    stdio_init_all();

    // Configuração dos GPIOs
    gpio_init(LED_VERDE);
    gpio_init(LED_VERMELHO);
    gpio_init(LED_AZUL);
    gpio_init(BOTAO);

    gpio_set_dir(LED_VERDE, GPIO_OUT);
    gpio_set_dir(LED_VERMELHO, GPIO_OUT);
    gpio_set_dir(LED_AZUL, GPIO_OUT);
    gpio_set_dir(BOTAO, GPIO_IN);
    gpio_pull_up(BOTAO);

    // Configurar interrupção no botão
    gpio_set_irq_enabled_with_callback(BOTAO, GPIO_IRQ_EDGE_FALL, true, &pressionar_botao);

    while (1) {
        tight_loop_contents();
    }

    return 0;
}