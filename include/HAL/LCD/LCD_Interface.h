#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_

#define LCD_LINDE1 0
#define LCD_LINDE2 1

void LCD_voidInit(void);
void LCD_voidSendCmnd(u8 Copy_u8Cmnd);
void LCD_voidSendData(u8 Copy_u8Data);
u8 LCD_u8GoToXy(u8 Copy_u8LineNum, u8 Copy_u8Location);
void LCD_voidDisplayClear(void);
void LCD_voidSendString(u8 *Copy_pu8Data);
void LCD_voidDisplayNumber(s32 Copy_s32Number);
void LCD_voidDisplaySpecialCharacter(u8 *Copy_pu8Pattern, u8 Copy_u8Location);

#endif /* LCD_INTERFACE_H_ */