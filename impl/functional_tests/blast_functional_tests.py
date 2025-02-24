from selenium import webdriver
from selenium.common.exceptions import WebDriverException
from requests import get
import unittest, time, os, shutil

class NewVisitorTest(unittest.TestCase):

    def setUp(self):
        self.folder_location = os.path.dirname(os.path.realpath(__file__))
        self.download_path = os.path.join(self.folder_location, 'temp')

        options = webdriver.ChromeOptions()
        options.add_experimental_option("prefs", {
          "download.default_directory": self.download_path,
          "download.prompt_for_download": False,
          "download.directory_upgrade": True,
          "safebrowsing.enabled": True
        })
        self.browser = webdriver.Chrome(chrome_options=options)

    def tearDown(self):
        if(os.path.exists(self.download_path)):
            shutil.rmtree(self.download_path)
        self.browser.quit()

    def wait_for_file_to_download(self, filename, max_wait):
        start_time = time.time()
        path = os.path.join(self.download_path, filename)
        while time.time() - start_time < max_wait:
            time.sleep(1)
            if(os.path.isfile(path)):
                return True
        return False

    def find_by_id_and_check_text(self, id, text):
        field = self.browser.find_element_by_id(id)
        self.assertEqual(field.text, text)

    def test_can_add_assembly_task(self):

        #user enters the site and logs in as guest
        self.browser.get('http://localhost:9000')
        self.assertIn('DnaAssembler', self.browser.title)
        self.browser.find_element_by_id('loginAsGuestButton').click()

        #user goes to Files tab and uploads a file
        time.sleep(1)
        self.browser.find_element_by_id('a_user_tab_FILES').click()
        test_file = os.path.join(self.folder_location, 'blast_testfile')
        self.browser.find_element_by_id('chooseUploadFile').send_keys(test_file)
        self.browser.find_element_by_id('uploadFileButton').click()

        #on Assembling tab user can choose Long Reads Assembly 2
        self.browser.find_element_by_id('a_user_tab_ASSEMBLING').click()
        option = self.browser.find_element_by_xpath('//option[@value="long_reads_assembling_2"]')
        self.assertEqual(option.text, 'Long reads assembly 2')
        option.click()

        #user can see fields for assembly parameters
        self.find_by_id_and_check_text('label_enterName', 'Task name')
        self.find_by_id_and_check_text('label_inputFile', 'Input file')
        self.find_by_id_and_check_text('label_kmerSize', 'K-mer size')
        self.find_by_id_and_check_text('label_minSimilarity', 'Minimum similarity')

        #user fills input boxes and submits task
        self.browser.find_element_by_id('enterName').send_keys('Test 1')
        self.browser.find_element_by_id('add_inputFile_option_blast_testfile').click()
        self.browser.find_element_by_id('kmerSize').send_keys('20')

        #user cant submit task until all boxes are filled
        submit = self.browser.find_element_by_id('addTaskSubmitButton')
        self.assertFalse(submit.is_enabled())

        #user cant submit letter to number field
        self.browser.find_element_by_id('minSimilarity').send_keys('a')
        self.assertFalse(submit.is_enabled())
        self.browser.find_element_by_id('minSimilarity').send_keys('5')
        self.browser.find_element_by_id('addTaskSubmitButton').click()

        #user no longer see task form
        self.assertFalse(self.browser.find_element_by_xpath('//form').is_displayed())

        #user sees table with results
        table = self.browser.find_elements_by_xpath('//th')

        self.assertEqual(table[0].text, 'ID')
        self.assertEqual(table[1].text, 'Task name')
        self.assertEqual(table[2].text, 'Input file')
        self.assertEqual(table[3].text, 'K-mer size')
        self.assertEqual(table[4].text, 'Minimum similarity')
        self.assertEqual(table[5].text, 'Download result')

        results = self.browser.find_elements_by_xpath('//table[@id="taskTable"]//td')
        self.assertEqual(results[1].text, 'Test 1')
        self.assertEqual(results[2].text, 'blast_testfile')
        self.assertEqual(results[3].text, '20')
        self.assertEqual(results[4].text, '5')

        #user downloads file
        results[5].click()
        self.assertTrue(self.wait_for_file_to_download('Test 1', 2))

        #file contains expected result
        with open(os.path.join(self.download_path, 'Test 1')) as f:
            file_content = f.read()
        self.assertEqual(file_content, '@res_0\nAAAAACCCCCTTTTTGGGCTGTTCCGGC\n')


if __name__ == '__main__':
    unittest.main(warnings='ignore')
