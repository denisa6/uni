import { Component, OnInit } from '@angular/core';
import {GenericService} from '../generic.service';
import {Book} from '../book';
import {Router} from '@angular/router';

@Component({
  selector: 'app-show-books',
  templateUrl: './show-books.component.html',
  styleUrls: ['./show-books.component.css']
})
export class ShowBooksComponent implements OnInit{
	  books: Book[] = [];

  	constructor(private service: GenericService, private router: Router) {
  	}

  	ngOnInit(): void {
    	this.refresh('');
  	}

  	refresh(genre: string): void {
    	this.service.fetchBooks(genre).subscribe(books => this.books = books);
  	}

  	navigateToDelete(bid: number): void {
    	this.router.navigate(['deleteBook'], {queryParams: {id: bid}}).then(_ => {
    	});
  	}

  	navigateToAdd(): void {
    	this.router.navigate(['addBook']).then(_ => {
    	});
  	}

  	navigateToUpdate(bid: number): void {
    	this.router.navigate(['updateBook'], {queryParams: {id: bid}}).then(_ => {
    	});
  	}
}
