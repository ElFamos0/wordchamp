<template>
  <div class="hello">
    <h1>Bienvenue sur Wordchamp</h1> <!-- msg est une variable de template -->
    <ul>
      <li>Il faut utiliser les menus en haut pour se déplacer.</li>
    </ul>
  </div>
</template>

<script>
export default {
  name: 'home-page',
};
</script>

<!-- Add "scoped" attribute to limit CSS to this component only -->
<style scoped>
ul {
  list-style-type: none;
  padding: 0;
}
li {
  display: inline-block;
  margin: 0 10px;
}
</style>
