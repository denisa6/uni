import { Component, OnInit } from '@angular/core';
import {GenericService} from '../generic.service';
import {ActivatedRoute, Router} from '@angular/router';

@Component({
  selector: 'app-update-book',
  templateUrl: './update-book.component.html',
  styleUrls: ['./update-book.component.css']
})
export class UpdateBookComponent implements OnInit{
	constructor(private service: GenericService, private router: Router, private route: ActivatedRoute) { }

  	ngOnInit(): void {
  	}

  	updateBook(title: string, author: string, nrPages: string, genre: string, borrowed: string): void {
    	const id = this.route.snapshot.queryParams['id'];
    	this.service.updateBook(id, title, author, nrPages, genre, borrowed).subscribe(() => {
      		this.router.navigate(['showBooks']).then(_ => {
      		});
    	});
  	}

  	onCancel(): void {
    	this.router.navigate(['showBooks']).then(_ => {
    	});
  	}
}
