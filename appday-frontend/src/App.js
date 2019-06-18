import React from 'react';
import './App.css';
import { BrowserRouter, Route } from 'react-router-dom';
import Season from './components/season';
import Match from './components/Match';
import Points from './components/Points';

function App() {
  return (
    <BrowserRouter>
            <div>
              {/* All routes */}
              <Route path="/" exact component={Season} />
              <Route path="/matches/:match_id" exact component={Match} />
              <Route path="/points" exact component={Points} />
            </div>
          </BrowserRouter>
  );
}

export default App;
