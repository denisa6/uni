from django.db import models
from django.db.models.deletion import CASCADE

class Book(models.Model):
    title = models.CharField(max_length=100, unique=True)
    publishing_date = models.CharField(max_length=100)
    publisher = models.CharField(max_length=100)
    description = models.CharField(max_length=500)
    price = models.DecimalField(max_digits=10, decimal_places=2)

    def __str__(self):
        return self.title

class Author(models.Model):
    first_name = models.CharField(max_length=100, unique=True)
    last_name = models.CharField(max_length=100)
    agent = models.CharField(max_length=100)
    date_of_birth = models.CharField(max_length=500)
    country_of_origin = models.CharField(max_length=500)
    members = models.ManyToManyField(Book, through="BookAuthors")

    def __str__(self):
        return self.first_name + " " + self.last_name


# a bookstore has one book that is their best seller
# a book can be the best seller of multiple bookstores
class BookStore(models.Model):
    store_name = models.CharField(max_length=100, unique=True)
    store_manager = models.CharField(max_length=100)
    store_location = models.CharField(max_length=100)
    store_country = models.CharField(max_length=500)
    founding_year = models.IntegerField(default=2000)
    best_seller = models.ForeignKey(Book, related_name='book_stores', on_delete=models.CASCADE)

    def __str__(self):
        return self.store_name 


class BookAuthors(models.Model):
    book = models.ForeignKey(Book, related_name='authors', on_delete=models.CASCADE)
    author = models.ForeignKey(Author, related_name='books', on_delete=models.CASCADE)
    contribution = models.CharField(max_length=500)
    author_comments = models.CharField(max_length=500)
