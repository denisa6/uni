import {Injectable} from '@angular/core';
import {HttpClient, HttpHeaders} from '@angular/common/http';

import {Observable, of} from 'rxjs';
import {catchError} from 'rxjs/operators';
import {Book} from './book';

@Injectable({
  providedIn: 'root'
})

export class GenericService {
  httpOptions = {
    headers: new HttpHeaders({
      'Content-Type': 'application/json'
    })
  };
  private backendUrl = 'http://localhost/lab8v2/php/';

  constructor(private http: HttpClient) {
  }

  fetchBooks(genre: string): Observable<Book[]> {
    /* body of the method */
    return this.http.get<Book[]>(this.backendUrl + `showBooks.php?genre=${genre}`)
      .pipe(catchError(this.handleError<Book[]>('fetchBooks', []))
      );
  }

  deleteBook(bid: number): Observable<any> {
    return this.http.post(this.backendUrl + `deleteBookBackend.php`, {id: bid});
  }

  addBook(titleOf: string, authorOf: string, nrPagesOf: string, genreOf: string, borrowedOf: string): Observable<any> {
    return this.http.post(this.backendUrl + `addBook.php`, {
      title: titleOf,
      author: authorOf,
      nrPages: nrPagesOf,
      genre: genreOf,
      borrowed: borrowedOf
    });
  }

  updateBook(idOf: number, titleOf: string, authorOf: string, nrPagesOf: string, genreOf: string, borrowedOf: string): Observable<any> {
    return this.http.post(this.backendUrl + `updateBookBackend.php`, {
      id: idOf,
      title: titleOf,
      author: authorOf,
      nrPages: nrPagesOf,
      genre: genreOf,
      borrowed: borrowedOf
    });
  }

  private handleError<T>(operation = 'operation', result?: T): (error: any) => Observable<T> {
    return (error: any): Observable<T> => {
      console.error(error);
      return of(result as T);
    };
  }
}
