void play_audio(uint8_t track)
{
    if (track == 0) return; // DND in idle
    
    switch (track)
    {
        case 1: PORTD &= ~(1 << TRIGGER1); break;
        case 2: PORTD &= ~(1 << TRIGGER2); break;
        case 3: PORTD &= ~(1 << TRIGGER3); break;
        case 4: PORTD &= ~(1 << TRIGGER4); break;
        default: return;
    }
    _delay_ms(2000);
    PORTD |= (1 << TRIGGER1) | (1 << TRIGGER2) | (1 << TRIGGER3) | (1 << TRIGGER4);
}