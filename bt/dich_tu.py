import sys
from deep_translator import GoogleTranslator

# Set encoding
sys.stdout.reconfigure(encoding='utf-8')

def translate_word(word):
    try:
        # Dịch sang tiếng Việt
        translated = GoogleTranslator(source='en', target='vi').translate(word)
        
        # LOGIC KIỂM TRA TỪ VÔ NGHĨA
        # Nếu từ dịch ra y hệt từ gốc (bỏ qua hoa thường) -> Khả năng cao là từ vô nghĩa
        if translated.lower().strip() == word.lower().strip():
            return "#INVALID"
            
        return translated
    except Exception as e:
        return "" 

if __name__ == "__main__":
    if len(sys.argv) > 1:
        word_to_translate = " ".join(sys.argv[1:])
        print(translate_word(word_to_translate))
    else:
        print("")