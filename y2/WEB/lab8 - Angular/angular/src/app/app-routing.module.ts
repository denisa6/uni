import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';
import {ShowBooksComponent} from './show-books/show-books.component';
import {DeleteBookComponent} from './delete-book/delete-book.component';
import {AddBookComponent} from './add-book/add-book.component';
import {UpdateBookComponent} from './update-book/update-book.component';

const routes: Routes = [
	{path: '', redirectTo: '/showBooks', pathMatch: 'full'},
  	{path: 'showBooks', component: ShowBooksComponent},
  	{path: 'deleteBook', component: DeleteBookComponent},
  	{path: 'addBook', component: AddBookComponent},
  	{path: 'updateBook', component: UpdateBookComponent}
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule { }
