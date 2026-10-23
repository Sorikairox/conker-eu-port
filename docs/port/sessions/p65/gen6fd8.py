import itertools
for idv, latch, e35, flg, x in itertools.product([0x3B,0x75,0x81,0x10,0xB4,0xB5],[0,1,2],[0,1,2],[0,1],[0,1]):
    p = ['800C4298=00000000', '800CC6F4=%02X000000' % idv, '800CCA14=80480000', '800C4418=0000%02X00' % latch,
         '800C3A08=0000%02X00' % e35, '800D196C=80470000', '804702F8=%04X0000' % (0x100 * flg + 0x23),
         '80480000=%s' % ('C7C34F80' if x else '3F800000')]
    print('i%02X_l%d_e%d_f%d_x%d ! ! %s ! !' % (idv, latch, e35, flg, x, ','.join(p)))
