import { Component, OnInit } from '@angular/core';
import {GenericService} from '../generic.service';
import {Router} from '@angular/router';

@Component({
  selector: 'app-add-book',
  templateUrl: './add-book.component.html',
  styleUrls: ['./add-book.component.css']
})
export class AddBookComponent implements OnInit{
	constructor(private service: GenericService, private router: Router) {
  	}

  	ngOnInit(): void {
  	}

  	addBook(title: string, author: string, nrPages: string, genre: string, borrowed: string): void {
    	this.service.addBook(title, author, nrPages, genre, borrowed).subscribe(() => {
      		this.router.navigate(['showBooks']).then(_ => {
      		});
    	});
  	}

  	onCancel(): void {
    	this.router.navigate(['showBooks']).then(_ => {
    	});
  	}
}
