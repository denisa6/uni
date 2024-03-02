from django.test import TestCase
from rest_framework.test import APITestCase, APIClient
from rest_framework import status
from api.models import Book, Author, BookAuthors, BookStore
# Create your tests here.

class BooksByPrice(APITestCase):
    def setUp(self):
        self.book1 = Book.objects.create(id=1, title='Book1', publishing_date='12/03/2000', description='great', price=10)
        self.book2 = Book.objects.create(id=2, title='Book2', publishing_date='12/03/2000', description='great', price=100)
        self.book3 = Book.objects.create(id=3, title='Book3', publishing_date='12/03/2000', description='great', price=24)

    def test_books_by_price(self):
        response = self.client.get('/api/findbooks/')
        self.assertEqual(response.status_code, status.HTTP_200_OK)
        self.assertEqual(len(response.data), 3)
        self.assertEqual(response.data[0]['title'], 'Book1')

    def test_books_by_price_no_result(self):
        response = self.client.get('/api/findbooks/?var=150')
        self.assertEqual(response.status_code, status.HTTP_200_OK)
        self.assertEqual(len(response.data), 0)


class AuthorsByAvgBookPriceTest(TestCase):
    def setUp(self):
        self.client = APIClient()
        self.author1 = Author.objects.create(id=1, first_name='Ana', last_name='Pop', agent='Gary Brendon', date_of_birth='12/05/1999', country_of_origin='Sudan')
        self.author2 = Author.objects.create(id=2, first_name='Andrei', last_name='Popescu', agent='Sonya Brem', date_of_birth='12/05/2000', country_of_origin='Kenya')
        self.book1 = Book.objects.create(id=1, title='Book1', publishing_date='15/04/2000', description='super', price=10)
        self.book2 = Book.objects.create(id=2, title='Book2', publishing_date='12/03/2000', description='great', price=100)
        self.bookauthors1 = BookAuthors.objects.create(id=1, book=self.book1, author=self.author1, contribution='what matters', author_comments='super')
        self.bookauthors2 = BookAuthors.objects.create(id=2, book=self.book2, author=self.author1, contribution='just right', author_comments='cool')
        self.bookauthors3 = BookAuthors.objects.create(id=3, book=self.book2, author=self.author2, contribution='amazing', author_comments='cooler')

    def test_authors_by_avg_book_price(self):
        response = self.client.get('/api/authors/avg-smth/')
        self.assertEqual(response.status_code, status.HTTP_200_OK)
        self.assertEqual(len(response.data), 2)

        self.assertEqual(response.data[1]['first_name'], 'Andrei')
        self.assertEqual(response.data[1]['last_name'], 'Popescu')
        self.assertEqual(response.data[1]['agent'], 'Sonya Brem')
        self.assertEqual(response.data[1]['date_of_birth'], '12/05/2000')
        self.assertEqual(response.data[1]['country_of_origin'], 'Kenya')
        self.assertEqual(response.data[1]['avg_price'], 100)

        self.assertEqual(response.data[0]['first_name'], 'Ana')
        self.assertEqual(response.data[0]['last_name'], 'Pop')
        self.assertEqual(response.data[0]['agent'], 'Gary Brendon')
        self.assertEqual(response.data[0]['date_of_birth'], '12/05/1999')
        self.assertEqual(response.data[0]['country_of_origin'], 'Sudan')
        self.assertEqual(response.data[0]['avg_price'], 55)
        