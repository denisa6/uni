from django.db.models.fields import DecimalField
from rest_framework import serializers
from .models import Book, Author, BookStore, BookAuthors
from django.db.models import Avg


class AuthorSerializer(serializers.ModelSerializer):
    class Meta:
        model = Author
        fields = ('__all__')

class BookSerializer2(serializers.ModelSerializer):
    class Meta:
        model = Book
        fields = ('__all__')


class BookStoreSerializerList(serializers.ModelSerializer):
    class Meta:
        model = BookStore
        fields = ('__all__')


class BookSerializer(serializers.ModelSerializer):
    book_stores = BookStoreSerializerList(read_only=True, many=True)

    class Meta:
        model = Book
        fields = ['id', 'title', 'publishing_date', 'publisher', 'description', 'price', 'book_stores']

class BookSerializerList(serializers.ModelSerializer):
    class Meta:
        model = Book
        fields = ['id', 'title', 'publishing_date', 'publisher', 'description', 'price']
 

class BookStoreSerializer(serializers.ModelSerializer):
    best_seller = BookSerializer2(read_only=True)

    class Meta:
        model = BookStore
        fields = ['id', 'store_name', 'store_manager', 'store_location', 'store_country', 'best_seller']


class BookAuthorsSerializer(serializers.ModelSerializer):
    class Meta:
        model = BookAuthors
        fields = ('__all__')


class AuthorFilterSerializer(serializers.ModelSerializer):
    avg_price = serializers.FloatField(read_only=True)    
    class Meta:
        model = Author
        fields = ['first_name', 'last_name', 'agent', 'date_of_birth', 'country_of_origin', 'avg_price']

class BookFilterSerializer(serializers.ModelSerializer):
    avg_year = serializers.FloatField(read_only=True)
    book_stores = BookStoreSerializerList(read_only=True, many=True)

    class Meta:
        model = Book
        fields = ['id', 'title', 'publishing_date', 'publisher', 'description', 'price', 'book_stores', 'avg_year']
