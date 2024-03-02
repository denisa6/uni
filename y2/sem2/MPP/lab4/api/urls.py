from django.urls import path
from .views import BookList, BookDetail, AuthorList, AuthorDetail, BookStoreList, BookStoreDetail, BooksByPrice, \
    BookAuthorsDetail, BookAuthorsList, AuthorsByAvgBookPrice, BooksByNrOfBestSeller, BookStoreForBook

urlpatterns = [
    path('books/', BookList.as_view()),
    path('books/<int:pk>/', BookDetail.as_view()),
    path('authors/', AuthorList.as_view()),
    path('authors/<int:pk>/', AuthorDetail.as_view()),
    path('bookstores/', BookStoreList.as_view()),
    path('bookstores/<int:pk>/', BookStoreDetail.as_view()),
    path('bookauthors/', BookAuthorsList.as_view()),
    path('bookauthors/<int:pk>/', BookAuthorsDetail.as_view()),
    path('findbooks/', BooksByPrice.as_view()),
    path('authors/avg-smth/', AuthorsByAvgBookPrice.as_view()),
    path('books/count-smth/', BooksByNrOfBestSeller.as_view()),
    path('books/<int:pk>/bookstores/', BookStoreForBook.as_view())
]