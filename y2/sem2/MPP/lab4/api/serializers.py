from django.db.models.fields import DecimalField
from rest_framework import serializers
from rest_framework.response import Response
from .models import Book, Author, BookStore, BookAuthors
from django.db.models import Avg
from django.shortcuts import render, get_object_or_404



class BookSerializer2(serializers.ModelSerializer):
    class Meta:
        model = Book
        fields = ('__all__')


class BookStoreSerializerList(serializers.ModelSerializer):
    class Meta:
        model = BookStore
        fields = ('__all__')

    def validate_founding_year(self, value):
        if value <= 2023:
            return value
        raise serializers.ValidationError('The provided year is not valid')


class BookSerializerList(serializers.ModelSerializer):
    class Meta:
        model = Book
        fields = ['id', 'title', 'publishing_date', 'publisher', 'description', 'price']

    def validate_price(self, value):
        if value > 0:
            return value
        raise serializers.ValidationError('The provided price is not valid')

    def validate_title(self, value):
        if value[0] not in 'abcdefghijklmnopqrstuvwxyz':
            return value
        raise serializers.ValidationError('The provided title is not valid')
 

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


class BookSerializer(serializers.ModelSerializer):
    book_stores = BookStoreSerializerList(read_only=True, many=True)
    authors = BookAuthorsSerializer(read_only=True, many=True)

    class Meta:
        model = Book
        fields = ['id', 'title', 'publishing_date', 'publisher', 'description', 'price', 'book_stores', 'authors']


class AuthorSerializer(serializers.ModelSerializer):
    books = BookAuthorsSerializer(read_only=True, many=True)


    class Meta:
        model = Author
        fields = ['id', 'first_name', 'last_name', 'agent', 'date_of_birth', 'country_of_origin', 'books']

class AuthorSerializerList(serializers.ModelSerializer):
    class Meta:
        model = Author
        fields = ['id', 'first_name', 'last_name', 'agent', 'date_of_birth', 'country_of_origin']


class BookStoreForBookSerializer(serializers.ModelSerializer):
    id = serializers.IntegerField()

    def create(self, validated_data):
        bookstore_id = validated_data['id']
        bookstore = get_object_or_404(BookStore, pk=bookstore_id)
        bookstore.best_seller = validated_data['best_seller']
        db = validated_data.get('using', None)
        bookstore.save(using=db)
        return bookstore

    class Meta:
        model = BookStore
        fields = ['id']

"""
class FolderFilesEndpoint(views.APIView):
    def post(self, request, pk):
        serializer = FolderFilesSerializerList(data=request.data, many=True)
        folder = get_object_or_404(Folder, id=pk)
        serializer.context['folder'] = folder
        if serializer.is_valid():
            serializer.save(folder=folder, using='')
            return Response(serializer.data, status=status.HTTP_201_CREATED)
        return Response(serializer.errors, status=status.HTTP_204_NO_CONTENT)


class FolderFilesSerializerList(serializers.ModelSerializer):
    id = serializers.IntegerField()

    def validate_id(self, file_id):
        file = get_object_or_404(File, pk=file_id)
        folder = self.context['folder']
        if file.user != folder.user:
            raise serializers.ValidationError('File and folder must be created by the same user.')
        return file_id

    def create(self, validated_data):
        file_id = validated_data['id']
        file = get_object_or_404(File, pk=file_id)
        file.folder = validated_data['folder']
        db = validated_data.get('using', None)
        file.save(using=db)
        return file

    class Meta:
        model = File
        fields = ['id']
"""
