from django.shortcuts import render, get_object_or_404
from rest_framework.response import Response
from django.http import Http404
from django.db.models import query
from django.db.models import Avg, Count
from django.db.models.expressions import OuterRef
from rest_framework import generics, views, status
from .models import Book, Author, BookStore, BookAuthors
from .serializers import BookSerializer, AuthorSerializer, BookStoreSerializer, BookSerializerList, BookStoreSerializerList, \
    BookAuthorsSerializer, AuthorFilterSerializer, BookFilterSerializer, AuthorSerializerList, BookStoreForBookSerializer


class BookList(generics.ListCreateAPIView):
    serializer_class = BookSerializerList
    queryset = Book.objects.all()


class BookDetail(generics.RetrieveUpdateDestroyAPIView):
    serializer_class = BookSerializer
    queryset = Book.objects.all()


class AuthorList(generics.ListCreateAPIView):
    serializer_class = AuthorSerializerList
    queryset = Author.objects.all()


class AuthorDetail(generics.RetrieveUpdateDestroyAPIView):
    serializer_class = AuthorSerializer
    queryset = Author.objects.all()


class BookStoreList(generics.ListCreateAPIView):
    serializer_class = BookStoreSerializerList

    def get_queryset(self):
        queryset = BookStore.objects.all()
        book = self.request.query_params.get('best_seller')
        if book is not None:
            queryset = queryset.filter(best_seller=book)
        return queryset


class BookStoreDetail(generics.RetrieveUpdateDestroyAPIView):
    serializer_class = BookStoreSerializer
    queryset = BookStore.objects.all()


class BooksByPrice(generics.ListCreateAPIView):
    serializer_class = BookSerializer

    def get_queryset(self):
        queryset = Book.objects.all()
        var = self.request.GET.get('var', 0)
        if var is not None:
            queryset = queryset.filter(price__gt=var)        
        return queryset


class BookAuthorsList(generics.ListCreateAPIView):
    serializer_class = BookAuthorsSerializer

    def get_queryset(self):
        queryset = BookAuthors.objects.all()
        book = self.request.query_params.get('book')
        author = self.request.query_params.get('author')
        if book is not None and author is not None:
            queryset = queryset.filter(book=book).filter(author=author)
        return queryset


class BookAuthorsDetail(generics.RetrieveUpdateDestroyAPIView):
    serializer_class = BookAuthorsSerializer
    queryset = BookAuthors.objects.all()


# show all authors orderded by the price of their books
class AuthorsByAvgBookPrice(generics.ListAPIView):
    serializer_class = AuthorFilterSerializer

    def get_queryset(self):
        query = Author.objects\
            .annotate(avg_price=Avg('bookauthors__book__price'))\
            .order_by('avg_price')
        print(query.query)

        return query

# books by the number of stores they are best seller in
class BooksByNrOfBestSeller(generics.ListAPIView):
    serializer_class = BookFilterSerializer

    def get_queryset(self):
        #query = Book.objects.annotate(count=Count(BookStore.objects.all().filter(best_seller=OuterRef('pk')))).order_by('count')
        query = Book.objects\
            .annotate(avg_year=Count('book_stores__founding_year'))\
            .order_by('avg_year')
        print(query.query)
        print(query.query)
        return query


class BookStoreForBook(views.APIView):
    def post(self, request, pk):
        serializer = BookStoreForBookSerializer(data=request.data, many=True)
        """
        try:
            best_seller = Book.objects.get(id=pk)
        except Book.DoesNotExist:
            raise Http404("No MyModel matches the given query.")"""
        best_seller = get_object_or_404(Book, id=pk)
        serializer.context['best_seller'] = best_seller
        if serializer.is_valid():
            serializer.save(best_seller=best_seller, using='')
            return Response(serializer.data, status=status.HTTP_201_CREATED)
        return Response(serializer.errors, status=status.HTTP_204_NO_CONTENT)