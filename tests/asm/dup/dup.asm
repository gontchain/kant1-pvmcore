{
    0xF1F2F3
    0xF4F5F6
    0xF7F8F9
    0xF0F0F0
    dup2
    dup4
    add // 0xF4F5F6 + 0xF7F8F9
    0x00
    mstore
    pop
    pop
    pop
    pop
    0x04
    0x1c
    return // 0x01ECEEEF
}
