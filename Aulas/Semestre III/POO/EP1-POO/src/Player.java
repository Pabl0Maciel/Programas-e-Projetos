import java.awt.*;
import java.awt.image.BufferedImage;
import java.util.Timer;
import java.util.TimerTask;

/**
	Esta classe representa os jogadores (players) do jogo. A classe principal do jogo
	instancia dois objetos deste tipo quando a execução é iniciada.
*/
public class Player implements ISolid {
	private double direction;
	private double cx, cy, width, height, speed;
	private Color color;
	private String id;
	private BufferedImage img;

	private long lastShotTime = 0;
	private static final long fireCooldown = 300; // em milissegundos

	private long deathTime = 0;



	/**
		Construtor da classe Player.

		@param cx coordenada x da posição inicial do player (centro do retângulo que o representa).
		@param cy coordenada y da posição inicial do player (centro do retângulo que o representa).
		@param width largura do retângulo que representa o player.
		@param height altura do retângulo que representa o player.
		@param angle direção apontada pelo player
		@param sprite gráfico do player
		@param color cor do player.
		@param id uma string que identifica o player
		@param speed velocidade do movimento do player.
	*/
	public Player(double cx, double cy, double width, double height, double angle, BufferedImage sprite, Color color, String id, double speed){
		this.cx = cx;
		this.cy = cy;
		this.width = width;
		this.height = height;
		this.color = color;
		this.id = id;
		this.direction = angle;
		this.speed = speed;
		this.img = sprite;
	}

	/**
		Método chamado sempre que o player precisa ser (re)desenhado.
	*/
	public void draw(){
		GameLib.setColor(color);

		if (isDead()) {
			long now = System.currentTimeMillis();
			GameLib.drawImage(img, cx, cy, direction + now % 60 * 60, width / img.getWidth());
			return;
		}

		GameLib.drawImage(img, cx, cy, direction, width / img.getWidth());
	}

	/**
		Método chamado quando se deseja mover para a frente na direção atual. 
		Este método é chamado sempre que a tecla associada à ação 
		de mover o player para frente estiver pressionada.

		@param delta quantidade de milissegundos que se passou entre o ciclo anterior de atualização do jogo e o atual.
	*/
	public void moveForwards(long delta){
		if (!isDead()) {
			cx += Math.cos(Math.toRadians(direction)) * speed * delta;
			cy += Math.sin(Math.toRadians(direction)) * speed * delta;
		}
	}

	/**
		Método chamado quando se deseja mover o player para trás na direção atual. 
		Este método é chamado sempre que a tecla associada à ação 
		de mover o player para trás estiver pressionada.

		@param delta quantidade de milissegundos que se passou entre o ciclo anterior de atualização do jogo e o atual.
	*/
	public void moveBackwards(long delta){
		if (!isDead()) {
			cx -= Math.cos(Math.toRadians(direction)) * speed * delta;
			cy -= Math.sin(Math.toRadians(direction)) * speed * delta;
		}
	}

	/**
		Método chamado quando se deseja girar o player para a esquerda (sentido anti-horário). 
		Este método é chamado sempre que a tecla associada à ação 
		de rotacionar o player à esquerda estiver pressionada.

		@param delta quantidade de milissegundos que se passou entre o ciclo anterior de atualização do jogo e o atual.
	 */
	public void rotateLeft(long delta) {
		if (!isDead()) {
			direction -= 0.1 * delta;
		}
	}

	/**
		Método chamado quando se deseja girar o player para a direita (sentido horário). 
		Este método é chamado sempre que a tecla associada à ação 
		de rotacionar o player à direita estiver pressionada.

		@param delta quantidade de milissegundos que se passou entre o ciclo anterior de atualização do jogo e o atual.
	 */
	public void rotateRight(long delta) {
		if (!isDead()) {
			direction += 0.1 * delta;
		}
	}

	/**
	 * Retorna se o jogador pode realizar um disparo ou não. Chamado sempre que a ação de disparar
	 * desse player for acionada.
	 */
	public boolean canFire() {

		long now = System.currentTimeMillis();
		return ((now - lastShotTime) >= fireCooldown) && !isDead();
	}

	/**
	 * Cria um disparo vindo desse player na mesma direção apontada pelo player.
	 * Esse método cria o disparo e o adiciona ao jogo.
	 */
	public void fire() {
		double offset = this.height / 2 + 5.0 / 2 + 1; // altura do player + metade do tamanho do tiro + margem
		double startX = this.cx + Math.cos(Math.toRadians(this.direction)) * offset;
		double startY = this.cy + Math.sin(Math.toRadians(this.direction)) * offset;

		Shot shot = new Shot(this, startX, startY, 5.0, this.direction, 0.8);
		Combat.addShot(shot);
		lastShotTime = System.currentTimeMillis();
	}

	/**
	 * Retorna se o player acabou de ser destruído. Enquanto o player estiver destruído, ele não
	 * poderá ser danificado novamente.
	 */
	public boolean isDead() {

		if (this.id == null) return true;
		return false;
	}

	/**
	 * Chamado sempre que o player for destruído com um disparo. 
	 */
	public void die() {
		this.id = null;
		this.draw();

		this.deathTime = System.currentTimeMillis();
		new Timer().schedule(new TimerTask() {
			@Override
			public void run() {
				respawn(); // revive após o tempo
			}
		}, 2000);
	}


	public void respawn(){
		double[] pos = Map.getRandomRespawn();
		this.setPosition(pos[0], pos[1]);
		this.id = (this.color == Color.GREEN) ? "Player 1" : "Player 2";
		this.draw();
	}


	/**
		Método que devolve a string de identificação do player.
		@return a String de identificação.
	*/
	public String getId() { 
		return this.id;
	}

	/**
	 * Teleporta o player para essa coordenada do mapa.
	 */
	public void setPosition(double cx, double cy) {
		this.cx = cx;
		this.cy = cy;
	}

	/**
		Método que devolve a largura do retângulo que representa o player.
		@return um double com o valor da largura.
	*/
	public double getWidth() { 
		return this.width;
	}

	/**
		Método que devolve a altura do retângulo que representa o player.
		@return um double com o valor da altura.
	*/
	public double getHeight() { 
		return this.height;
	}

	/**
		Método que devolve a coordenada x do centro do retângulo que representa o player.
		@return o valor double da coordenada x.
	*/
	public double getCx() { 
		return this.cx;
	}

	/**
		Método que devolve a coordenada y do centro do retângulo que representa o player.
		@return o valor double da coordenada y.
	*/
	public double getCy() { 
		return this.cy;
	}

	/**
	 * Obtém a cor do player.
	 */
	public Color getColor() {
		return this.color;
	}
}

