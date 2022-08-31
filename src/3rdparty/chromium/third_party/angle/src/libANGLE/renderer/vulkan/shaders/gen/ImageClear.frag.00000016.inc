// GENERATED FILE - DO NOT EDIT.
// Generated by gen_vk_internal_shaders.py.
//
// Copyright 2020 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// shaders/gen/ImageClear.frag.00000016.inc:
//   Pre-generated shader for the ANGLE Vulkan back-end.

#pragma once
constexpr uint8_t kImageClear_frag_00000016[] = {
    0x1f,0x8b,0x08,0x00,0x00,0x00,0x00,0x00,0x02,0xff,0x2d,0x90,0xbd,0x0a,0xc2,0x50,
    0x0c,0x85,0x63,0x7f,0x6d,0xab,0xd6,0x2a,0xe2,0x56,0x94,0x8e,0x42,0x71,0x50,0x11,
    0x44,0xc1,0xa9,0x0e,0xdd,0x7c,0x02,0xc1,0xc5,0x41,0x17,0x7d,0x78,0x17,0xc1,0x73,
    0x6e,0xcf,0x85,0xdc,0x34,0x5f,0x4e,0x92,0x9b,0xfa,0x5e,0x15,0x9b,0xf5,0x2c,0xb5,
    0xbe,0x4d,0xac,0x3b,0x85,0x79,0x20,0x66,0x99,0x45,0xce,0x37,0xed,0xb5,0xad,0xdf,
    0x9f,0x7b,0xbd,0xd9,0xae,0x99,0x1f,0x99,0xef,0x74,0xcc,0xe5,0xd0,0x04,0xf0,0xb4,
    0xe7,0xed,0xf1,0x22,0x4f,0x60,0x63,0x68,0xc8,0x62,0xd6,0xe3,0x8b,0xac,0x84,0x45,
    0xb0,0x8b,0x85,0x98,0xd7,0x9d,0x4a,0xbe,0x81,0x9e,0xcc,0x83,0x4d,0x71,0xd3,0x2f,
    0xc1,0x7c,0xb1,0x19,0x7a,0xb0,0x76,0x21,0xfd,0x1c,0x71,0xac,0x7e,0x81,0xe3,0x01,
    0x36,0x30,0xa7,0x27,0x3f,0x28,0x4e,0xc4,0x4a,0xf5,0x8f,0xa5,0xcd,0x94,0x4b,0xa5,
    0x65,0x3c,0x10,0xe3,0xac,0xa1,0x66,0x71,0xc7,0x95,0xe2,0x91,0x66,0xb3,0x3e,0x97,
    0x96,0xfd,0x76,0xd8,0xc7,0xd3,0x3b,0x4c,0xf3,0xbe,0x20,0x21,0xfc,0x19,0x77,0xee,
    0xfe,0x47,0xd7,0x9f,0x3d,0x8e,0x7a,0x7b,0x21,0x7e,0x42,0x45,0xa2,0xf8,0x87,0x89,
    0x7b,0xd8,0x1f,0xcb,0xf0,0x64,0x1f,0x98,0x01,0x00,0x00
};

// Generated from:
//
// #version 450 core
//
// layout(push_constant)uniform PushConstants {
//        uvec4 clearColor;
// } params;
//
// layout(location = 6)out uvec4 colorOut;
//
// void main()
// {
//     colorOut = params . clearColor;
// }