CRGBPalette16 viridis(
    {0xfde725, 0xd2e21b, 0xa5db36, 0x7ad151, 0x54c568, 0x35b779, 0x22a884,
    0x1f988b, 0x23888e, 0x2a788e, 0x31688e, 0x39568c, 0x414487, 0x472f7d,
    0x481a6c, 0x440154});

CRGBPalette16 inferno(
    {0xfcffa4, 0xf2e661, 0xfac62d, 0xfca50a, 0xf8850f, 0xed6925, 0xdd513a,
    0xc73e4c, 0xae305c, 0x932667, 0x781c6d, 0x5d126e, 0x420a68, 0x240c4f,
    0x0c0826, 0x000004});

CRGBPalette16 magma(
    {0xfcfdbf, 0xfddea0, 0xfebf84, 0xfe9f6d, 0xfa7f5e, 0xf1605d, 0xde4968,
    0xc43c75, 0xa8327d, 0x8c2981, 0x721f81, 0x57157e, 0x3b0f70, 0x20114b,
    0x0b0924, 0x000004});

CRGBPalette16 plasma(
    {0xf0f921, 0xf9dc24, 0xfec029, 0xfca636, 0xf68f44, 0xed7953, 0xe16462,
    0xd35171, 0xc33d80, 0xb12a90, 0x9c179e, 0x8405a7, 0x6a00a8, 0x5002a2,
    0x330597, 0x0d0887});

DEFINE_GRADIENT_PALETTE( heatmap_gp ) {
  0,     0,  0,  255,   // black
128,   255,  0,  0,   // red
224,   255,255,  0,   // bright yellow
255,   255,255,255 }; // full white
CRGBPalette16 heatmap = heatmap_gp;