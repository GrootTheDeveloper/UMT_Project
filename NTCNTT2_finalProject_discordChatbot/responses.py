import csv
from fuzzywuzzy import fuzz, process
from underthesea import text_normalize

def read_csv_to_dict(file_path):
    qa_pairs = {}
    with open(file_path, newline='', encoding='utf-8') as csvfile:
        reader = csv.DictReader(csvfile, quoting=csv.QUOTE_MINIMAL)
        for row in reader:
            qa_pairs[row['question'].strip()] = row['answer'].strip()
    return qa_pairs

qa_pairs = read_csv_to_dict('qa_pairs.csv')
def correct_spelling(question):
    return text_normalize(question)

def find_answer(question):
    corrected_question = correct_spelling(question)
    best_match = process.extractOne(corrected_question, qa_pairs.keys(), scorer=fuzz.token_set_ratio)
    if best_match[1] >= 60:
        return qa_pairs[best_match[0]]
    else:
        return "Xin lỗi, tôi không hiểu câu hỏi của bạn. Vui lòng liên hệ bộ phận tuyển sinh để được hỗ trợ thêm."



